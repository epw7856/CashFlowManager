#ifndef INVESTMENTTYPE_H
#define INVESTMENTTYPE_H

#include <string>

class InvestmentType
{
public:
    InvestmentType(std::string inputName, double inputTarget);

    std::string getName() const;

    double getMonthlyTarget() const;

private:
    std::string name = "";
    double monthlyTarget = 0.00;
};

#endif // INVESTMENTTYPE_H
