#include "supplementalincome.h"

SupplementalIncome::SupplementalIncome
(
    const QDate& inputDate
)
:
    BaseTransaction(inputDate, 0.0)
{

}

SupplementalIncome::SupplementalIncome
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

std::string SupplementalIncome::getDescription() const
{
    return description;
}
