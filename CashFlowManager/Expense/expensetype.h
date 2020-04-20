#ifndef EXPENSETYPE_H
#define EXPENSETYPE_H

#include <string>

class ExpenseType
{
public:
    ExpenseType(std::string name, unsigned monthlyBudget)
    :
        expenseName(name),
        expenseBudget(monthlyBudget){}

    std::string getName() const { return expenseName; }
    unsigned getMonthlyBudget() const { return expenseBudget; }

private:
    std::string expenseName = "";
    unsigned expenseBudget = 0U;

};

#endif // EXPENSETYPE_H
