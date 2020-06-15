#include "addexpensetransactiondialogcontroller.h"
#include "expenseinterface.h"
#include "expensetransaction.h"
#include "expensetype.h"
#include "mortgageinterface.h"
#include "mortgageprincipalpayment.h"
#include "validator.h"
#include <QDoubleValidator>
#include <QRegExp>

AddExpenseTransactionDialogController::AddExpenseTransactionDialogController
(
    ExpenseInterface &localExpenseInterface,
    MortgageInterface &localMortgageInterface
)
:
    expenseInterface(localExpenseInterface),
    mortgageInterface(localMortgageInterface)
{

}

QStringList AddExpenseTransactionDialogController::getExpenseTypes() const
{
    QStringList expenseTypes;
    for(const auto& type : expenseInterface.getExpenseTypes())
    {
        expenseTypes << QString::fromStdString(type->getName());
    }
    return expenseTypes;
}

bool AddExpenseTransactionDialogController::verifyTransactionDescription(QString description) const
{
    return Validator::verifyDescription(description);
}

bool AddExpenseTransactionDialogController::verifyTransactionDate(QDate date) const
{
    return Validator::verifyDate(date);
}

bool AddExpenseTransactionDialogController::verifyTransactionAmount(QString amount, bool zeroAllowed) const
{
    return Validator::verifyAmount(amount, zeroAllowed);
}

void AddExpenseTransactionDialogController::addExpenseTransaction(const QDate& date, const QString& type, const QString& description, double transactionAmount, double additionalPrincipal)
{
    ExpenseTransaction transaction(date, transactionAmount, description.toStdString());
    expenseInterface.addExpenseTransactionByType(type.toStdString(), transaction);
    if((type == "Mortgage") && (additionalPrincipal > 0.0))
    {
        MortgagePrincipalPayment payment(date, additionalPrincipal);
        mortgageInterface.addAdditionalPrincipalPayment(payment);
    }
}
