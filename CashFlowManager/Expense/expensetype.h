#ifndef EXPENSETYPE_H
#define EXPENSETYPE_H

#include <string>

class ExpenseType
{
public:
    ExpenseType(std::string inputName, double inputBudget);

    std::string getName() const;

    double getMonthlyBudget() const;

private:
    std::string name = "";
    double monthlyBudget = 0.00;
};

#endif // EXPENSETYPE_H
