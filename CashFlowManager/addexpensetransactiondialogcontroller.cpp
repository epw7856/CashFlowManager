#include "addexpensetransactiondialogcontroller.h"
#include "expenseinterface.h"
#include "expensetransaction.h"
#include "expensetype.h"
#include "mortgageinterface.h"
#include "mortgageprincipalpayment.h"
#include <QRegExp>
#include <QDoubleValidator>

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

bool AddExpenseTransactionDialogController::verifyDescription(QString description) const
{
    return (!description.isEmpty());
}

bool AddExpenseTransactionDialogController::verifyTransactionDate(QDate date) const
{
    return (date.year() <= QDate::currentDate().year() &&
            date.year() >= QDate::currentDate().addYears(-1).year());
}

bool AddExpenseTransactionDialogController::verifyAmount(QString amount, bool zeroAllowed) const
{
    QDoubleValidator validator;
    int pos = 0;

    (zeroAllowed) ? validator.setRange(0.00, 100000.00, 2) : validator.setRange(0.01, 100000.00, 2);

    return (validator.validate(amount, pos) == QValidator::Acceptable);
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
