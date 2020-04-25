#ifndef EXPENSETYPE_H
#define EXPENSETYPE_H

#include <string>

class ExpenseType
{
public:
    ExpenseType
    (
        std::string inputName,
        double inputBudget
    )
    :
        name(inputName),
        monthlyBudget(inputBudget){}

    std::string getName() const;

    double getMonthlyBudget() const;

private:
    std::string name = "";
    double monthlyBudget = 0.00;
};

std::string ExpenseType::getName() const
{
    return name;
}

double ExpenseType::getMonthlyBudget() const
{
    return monthlyBudget;
}

#endif // EXPENSETYPE_H
