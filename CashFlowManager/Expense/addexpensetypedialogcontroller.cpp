#include "addexpensetypedialogcontroller.h"
#include "currencyutilities.h"
#include "dateutilities.h"
#include "expenseinterface.h"
#include "expensetransaction.h"
#include "expensetype.h"
#include "mortgageinterface.h"
#include <QDate>
#include "validator.h"
#include <vector>

AddExpenseTypeDialogController::AddExpenseTypeDialogController(ExpenseInterface& localExpenseInterface, MortgageInterface& localMortgageInterface)
:
    expenseInterface(localExpenseInterface),
    mortgageInterface(localMortgageInterface)
{

}

QStringList AddExpenseTypeDialogController::getExpenseTypes() const
{
    QStringList expenseTypes;
    for(const auto& type : expenseInterface.getExpenseTypes())
    {
        expenseTypes << QString::fromStdString(type->getName());
    }
    return expenseTypes;
}

bool AddExpenseTypeDialogController::verifyTypeName(QString name) const
{
    return Validator::verifyDescription(name);
}

bool AddExpenseTypeDialogController::verifyBudgetAmount(QString amount, bool zeroAllowed) const
{
    return Validator::verifyDoubleAmount(amount, 100000.00, zeroAllowed);
}

bool AddExpenseTypeDialogController::verifyUniqueTypeName(QString name)
{
    std::vector<ExpenseType*> types = expenseInterface.getExpenseTypes();

    auto itr = std::find_if(types.begin(), types.end(), [=] (const ExpenseType* type)
    {
        return (QString::fromStdString(type->getName()).toLower() == name.trimmed().toLower());
    });
    return (itr == types.end());
}

void AddExpenseTypeDialogController::addExpenseType(const QString& name,
                                                    double budgetAmount,
                                                    bool isRequired)
{
    ExpenseType type(name.trimmed().toStdString(), budgetAmount, isRequired);

    expenseInterface.addExpenseType(type);
}

void AddExpenseTypeDialogController::deleteExpenseType(const QString& name)
{
    expenseInterface.deleteExpenseType(name.toStdString());
}

void AddExpenseTypeDialogController::updateExpenseType(const QString& currentName,
                                                       const QString& updatedName,
                                                       double updatedAmount,
                                                       bool isRequired)
{
    expenseInterface.updateExpenseType(currentName.toStdString(), updatedName.trimmed().toStdString(), updatedAmount, isRequired);
}

QString AddExpenseTypeDialogController::getMonthlyBudgetAmount(QString name) const
{
    std::vector<ExpenseType*> types = expenseInterface.getExpenseTypes();

    auto itr = std::find_if(types.begin(), types.end(), [=] (const ExpenseType* type)
    {
        return (QString::fromStdString(type->getName()).toLower() == name.toLower());
    });

    if(itr != types.end())
    {
        return QString::fromStdString(CurrencyUtilities::formatCurrency((*itr)->getMonthlyBudget())).remove(0, 1);
    }
    return "0.00";
}

bool AddExpenseTypeDialogController::getRequiredExpenseFlag(QString name) const
{
    return expenseInterface.getExpenseTypeRequiredFlag(name.toStdString());
}

bool AddExpenseTypeDialogController::expenseTypeContainsYearlyTransactions(const QString& name)
{
    std::pair<QDate, QDate> dates = DateUtilities::getYearlyDates(QDate::currentDate().year());
    return (expenseInterface.getExpenseTransactionsTotalByTimePeriod(name.toStdString(), dates.first, dates.second) > 0.0);
}
