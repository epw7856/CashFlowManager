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
    return Validator::verifyDoubleAmount(amount, 100000.00, false);
}

bool UpdateAutomaticMonthlyPaymentsDialogController::verifyUniquePaymentName(QString account, QString description) const
{
    std::vector<AutomaticMonthlyPayment*> payments = expenseInterface.getAutomaticMonthlyPayments();

    auto itr = std::find_if(payments.begin(), payments.end(), [=] (const AutomaticMonthlyPayment* item)
    {
        return ((QString::fromStdString(item->getName()).toLower() == description.trimmed().toLower()) &&
                (QString::fromStdString(item->getAccount()).toLower() == account.trimmed().toLower()));
    });
    return (itr == payments.end());
}

void UpdateAutomaticMonthlyPaymentsDialogController::addAutomaticMonthlyPayment(const QString& account,
                                                                                const QString& description,
                                                                                double amount)
{
    AutomaticMonthlyPayment payment(description.trimmed().toStdString(), account.trimmed().toStdString(), amount);
    expenseInterface.addAutomaticMonthlyPayment(payment);
}

void UpdateAutomaticMonthlyPaymentsDialogController::deleteAutomaticMonthlyPayment(const QString& account,
                                                                                   const QString& description,
                                                                                   double amount)
{
    AutomaticMonthlyPayment payment(description.toStdString(), account.toStdString(), amount);
    expenseInterface.deleteAutomaticMonthlyPayment(payment);
}

void UpdateAutomaticMonthlyPaymentsDialogController::updateAutomaticMonthlyPayment(const QString& existingAccount,
                                                                                   const QString& existingDescription,
                                                                                   double existingAmount,
                                                                                   const QString& updatedAccount,
                                                                                   const QString& updatedDescription,
                                                                                   double updatedAmount)
{
    AutomaticMonthlyPayment existingPayment(existingDescription.toStdString(), existingAccount.toStdString(), existingAmount);
    AutomaticMonthlyPayment updatedPayment(updatedDescription.trimmed().toStdString(), updatedAccount.trimmed().toStdString(), updatedAmount);
    expenseInterface.updateAutomaticMonthlyPayment(existingPayment, updatedPayment);
}
