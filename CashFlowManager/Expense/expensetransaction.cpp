#include "expensetransaction.h"

ExpenseTransaction::ExpenseTransaction
(
    QDate inputDate,
    double inputAmount,
    std::string inputType,
    std::string inputDescription
)
:
    BaseTransaction(inputDate, inputAmount),
    type(inputType),
    description(inputDescription)
{

}

std::string ExpenseTransaction::getType() const
{
    return type;
}

std::string ExpenseTransaction::getDescription() const
{
    return description;
}
