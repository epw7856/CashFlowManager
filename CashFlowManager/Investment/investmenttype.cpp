#include "investmenttype.h"

InvestmentType::InvestmentType
(
    std::string inputName,
    double inputTarget
)
:
    name(inputName),
    monthlyTarget(inputTarget)
{

}

std::string InvestmentType::getName() const
{
    return name;
}

double InvestmentType::getMonthlyTarget() const
{
    return monthlyTarget;
}
