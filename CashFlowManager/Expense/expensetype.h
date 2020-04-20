#ifndef EXPENSETYPE_H
#define EXPENSETYPE_H

#include <string>

class ExpenseType
{
public:
    ExpenseType
    (
        std::string name,
        double monthlyBudget
    )
    :
        expenseName(name),
        expenseBudget(monthlyBudget) {}

    std::string getName() const { return expenseName; }
    double getMonthlyBudget() const { return expenseBudget; }

private:
    std::string expenseName = "";
    double expenseBudget = 0.00;
};

#endif // EXPENSETYPE_H
