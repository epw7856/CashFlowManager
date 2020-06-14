#include "addexpensetransactiondialogcontroller.h"
#include "expenseinterface.h"
#include "expensetype.h"
#include "mortgageinterface.h"

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
