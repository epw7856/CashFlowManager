#include "addinvestmenttransactiondialogcontroller.h"
#include "investmentinterface.h"
#include "investmenttransaction.h"
#include "investmenttype.h"
#include "validator.h"

AddInvestmentTransactionDialogController::AddInvestmentTransactionDialogController(InvestmentInterface& localInvestmentInterface)
:
    investmentInterface(localInvestmentInterface)
{

}

QStringList AddInvestmentTransactionDialogController::getInvestmentTypes() const
{
    QStringList investmentTypes;
    for(const auto& type : investmentInterface.getInvestmentTypes())
    {
        investmentTypes << QString::fromStdString(type->getName());
    }
    return investmentTypes;
}

bool AddInvestmentTransactionDialogController::verifyTransactionDate(QDate date) const
{
    return Validator::verifyDate(date);
}

bool AddInvestmentTransactionDialogController::verifyTransactionAmount(QString amount) const
{
    return Validator::verifyDoubleAmount(amount, 100000.00, false);
}

void AddInvestmentTransactionDialogController::addInvestmentTransaction(const QDate& date, const QString& type, double transactionAmount)
{
    InvestmentTransaction transaction(date, transactionAmount);
    investmentInterface.addInvestmentTransactionByType(type.toStdString(), transaction);
}
