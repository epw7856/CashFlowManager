#include "supplementalincome.h"

SupplementalIncome::SupplementalIncome
(
    QDate inputDate,
    double inputAmount,
    std::string inputDescription
)
:
    BaseTransaction(inputDate, inputAmount),
    description(inputDescription)
{

}

std::string SupplementalIncome::getDescription() const
{
    return description;
}
