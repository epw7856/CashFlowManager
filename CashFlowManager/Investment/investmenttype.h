#ifndef INVESTMENTTYPE_H
#define INVESTMENTTYPE_H

#include <string>

class InvestmentType
{
public:
    InvestmentType
    (
        std::string inputName,
        double inputTarget
    )
    :
        name(inputName),
        monthlyTarget(inputTarget){}

    std::string getName() const;

    double getMonthlyTarget() const;

private:
    std::string name = "";
    double monthlyTarget = 0.00;
};

#endif // INVESTMENTTYPE_H

std::string InvestmentType::getName() const
{
    return name;
}

double InvestmentType::getMonthlyTarget() const
{
    return monthlyTarget;
}
