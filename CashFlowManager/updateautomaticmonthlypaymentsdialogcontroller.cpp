#include "automaticmonthlypayment.h"
#include "expenseinterface.h"
#include <QString>
#include "updateautomaticmonthlypaymentsdialogcontroller.h"
#include "validator.h"

UpdateAutomaticMonthlyPaymentsDialogController::UpdateAutomaticMonthlyPaymentsDialogController(ExpenseInterface& localExpenseInterface)
:
    expenseInterface(localExpenseInterface)
{

}

bool UpdateAutomaticMonthlyPaymentsDialogController::verifyAccountName(QString description) const
{
    return Validator::verifyDescription(description);
}

bool UpdateAutomaticMonthlyPaymentsDialogController::verifyPaymentDescription(QString description) const
{
    return Validator::verifyDescription(description);
}

bool UpdateAutomaticMonthlyPaymentsDialogController::verifyTransactionAmount(QString amount) const
{
    return Validator::verifyDoubleAmount(amount, false);
}

void UpdateAutomaticMonthlyPaymentsDialogController::addAutomaticMonthlyPayment(const QString& account,
                                                                                const QString& description,
                                                                                double amount)
{
    AutomaticMonthlyPayment payment(description.toStdString(), account.toStdString(), amount);
    expenseInterface.addAutomaticMonthlyPayment(payment);
}

void UpdateAutomaticMonthlyPaymentsDialogController::deleteAutomaticMonthlyPayment(const QString& account,
                                                                                   const QString& description,
                                                                                   double amount)
{
    AutomaticMonthlyPayment payment(description.toStdString(), account.toStdString(), amount);
    expenseInterface.deleteAutomaticMonthlyPayment(payment);
}
