#ifndef AUTOMATICMONTHLYPAYMENT_H
#define AUTOMATICMONTHLYPAYMENT_H

#include <string>

class AutomaticMonthlyPayment
{
public:
    AutomaticMonthlyPayment
    (
        std::string inputName,
        std::string inputAccount,
        double inputAmount
    )
    :
        name(inputName),
        account(inputAccount),
        amount(inputAmount){}

    std::string getName() const;

    std::string getAccount() const;

    double getAmount() const;

private:
    std::string name = "";
    std::string account = "";
    double amount = 0.0;
};
#endif // AUTOMATICMONTHLYPAYMENT_H

std::string AutomaticMonthlyPayment::getName() const
{
    return name;
}

std::string AutomaticMonthlyPayment::getAccount() const
{
    return account;
}

double AutomaticMonthlyPayment::getAmount() const
{
    return amount;
}
