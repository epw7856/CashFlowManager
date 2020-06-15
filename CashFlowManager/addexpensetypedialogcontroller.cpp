#include "addexpensetypedialogcontroller.h"
#include "currencyutilities.h"
#include "expenseinterface.h"
#include "expensetransaction.h"
#include "expensetype.h"
#include "validator.h"
#include <vector>

AddExpenseTypeDialogController::AddExpenseTypeDialogController(ExpenseInterface& localExpenseInterface)
:
    expenseInterface(localExpenseInterface)
{

}

bool AddExpenseTypeDialogController::verifyTypeName(QString name) const
{
    return Validator::verifyDescription(name);
}

bool AddExpenseTypeDialogController::verifyBudgetAmount(QString amount, bool zeroAllowed) const
{
    return Validator::verifyAmount(amount, zeroAllowed);
}

bool AddExpenseTypeDialogController::verifyUniqueTypeName(QString name)
{
    std::vector<ExpenseType*> types = expenseInterface.getExpenseTypes();

    auto itr = std::find_if(types.begin(), types.end(), [=] (const ExpenseType* type)
    {
        return (QString::fromStdString(type->getName()).toLower() == name.toLower());
    });
    return (itr == types.end());
}

void AddExpenseTypeDialogController::addExpenseType(const QString& name, double budgetAmount)
{
    ExpenseType type(name.toStdString(), budgetAmount);

    expenseInterface.addExpenseType(type);
}

QString AddExpenseTypeDialogController::getFixedExpenseBudgetAmount(QString name) const
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
