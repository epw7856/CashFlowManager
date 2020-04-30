#include "expensetransaction.h"

ExpenseTransaction::ExpenseTransaction(const QDate& inputDate)
:
    BaseTransaction(inputDate, 0.0)
{

}

ExpenseTransaction::ExpenseTransaction
(
    const QDate& inputDate,
    double inputAmount,
    const std::string& inputDescription
)
:
    BaseTransaction(inputDate, inputAmount),
    description(inputDescription)
{

}

std::string ExpenseTransaction::getDescription() const
{
    return description;
}
