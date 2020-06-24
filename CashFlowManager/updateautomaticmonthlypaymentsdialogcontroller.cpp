#include "expenseinterface.h"
#include <QString>
#include "updateautomaticmonthlypaymentsdialogcontroller.h"
#include "validator.h"

UpdateAutomaticMonthlyPaymentsDialogController::UpdateAutomaticMonthlyPaymentsDialogController(ExpenseInterface& localExpenseInterface)
:
    expenseInterface(localExpenseInterface)
{

}

bool UpdateAutomaticMonthlyPaymentsDialogController::verifyPaymentDescription(QString description) const
{
    return Validator::verifyDescription(description);
}

bool UpdateAutomaticMonthlyPaymentsDialogController::verifyTransactionAmount(QString amount) const
{
    return Validator::verifyDoubleAmount(amount, false);
}
