#include "addinvestmenttypedialogcontroller.h"
#include "currencyutilities.h"
#include "dateutilities.h"
#include "investmentinterface.h"
#include "investmenttransaction.h"
#include "investmenttype.h"
#include "validator.h"

AddInvestmentTypeDialogController::AddInvestmentTypeDialogController(InvestmentInterface& localInvestmentInterace)
:
    investmentInterface(localInvestmentInterace)
{

}

QStringList AddInvestmentTypeDialogController::getInvestmentTypes() const
{
    QStringList investmentTypes;
    auto types = investmentInterface.getInvestmentTypes();
    for(const auto& type : types)
    {
        investmentTypes << QString::fromStdString(type->getName());
    }
    return investmentTypes;
}

bool AddInvestmentTypeDialogController::verifyTypeName(QString name) const
{
    return Validator::verifyDescription(name);
}

bool AddInvestmentTypeDialogController::verifyTargetAmount(QString amount) const
{
    return Validator::verifyDoubleAmount(amount, 100000.00, false);
}

bool AddInvestmentTypeDialogController::verifyUniqueTypeName(QString name)
{
    std::vector<InvestmentType*> types = investmentInterface.getInvestmentTypes();

    auto itr = std::find_if(types.begin(), types.end(), [=] (const InvestmentType* type)
    {
        return (QString::fromStdString(type->getName()).toLower() == name.toLower());
    });
    return (itr == types.end());
}

void AddInvestmentTypeDialogController::addInvestmentType(const QString& name, double targetAmount)
{
    InvestmentType type(name.toStdString(), targetAmount);

    investmentInterface.addInvestmentType(type);
}

void AddInvestmentTypeDialogController::deleteInvestmentType(const QString& name)
{
    investmentInterface.deleteInvestmentType(name.toStdString());
}

void AddInvestmentTypeDialogController::updateInvestmentType(const QString& currentName, const QString& updatedName, double updatedAmount)
{
    investmentInterface.updateInvestmentType(currentName.toStdString(), updatedName.toStdString(), updatedAmount);
}

QString AddInvestmentTypeDialogController::getMonthlyTargetAmount(QString name) const
{
    std::vector<InvestmentType*> types = investmentInterface.getInvestmentTypes();

    auto itr = std::find_if(types.begin(), types.end(), [=] (const InvestmentType* type)
    {
        return (QString::fromStdString(type->getName()).toLower() == name.toLower());
    });

    if(itr != types.end())
    {
        return QString::fromStdString(CurrencyUtilities::formatCurrency((*itr)->getMonthlyTarget())).remove(0, 1);
    }
    return "0.00";
}

bool AddInvestmentTypeDialogController::investmentTypeContainsYearlyTransactions(const QString& name)
{
    std::pair<QDate, QDate> dates = DateUtilities::getYearlyDates(QDate::currentDate().year());
    return (investmentInterface.getInvestmentTransactionsTotalByTimePeriod(name.toStdString(), dates.first, dates.second) > 0.0);
}
