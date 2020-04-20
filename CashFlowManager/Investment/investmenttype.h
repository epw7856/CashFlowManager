#ifndef INVESTMENTTYPE_H
#define INVESTMENTTYPE_H

#include <string>

class InvestmentType
{
public:
    InvestmentType(std::string name, unsigned monthlyTarget)
    :
        investmentName(name),
        investmentTarget(monthlyTarget){}

    std::string getName() const { return investmentName; }
    unsigned getMonthlyBudget() const { return investmentTarget; }

private:
    std::string investmentName = "";
    unsigned investmentTarget = 0U;

};

#endif // INVESTMENTTYPE_H
