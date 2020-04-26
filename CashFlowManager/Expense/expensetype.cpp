#include "expensetype.h"

ExpenseType::ExpenseType
(
    std::string inputName,
    double inputBudget
)
:
    name(inputName),
    monthlyBudget(inputBudget)
{

}

std::string ExpenseType::getName() const
{
    return name;
}

double ExpenseType::getMonthlyBudget() const
{
    return monthlyBudget;
}
