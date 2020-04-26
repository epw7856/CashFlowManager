#include "automaticmonthlypayment.h"

AutomaticMonthlyPayment::AutomaticMonthlyPayment
(
    std::string inputName,
    std::string inputAccount,
    double inputAmount
)
:
    name(inputName),
    account(inputAccount),
    amount(inputAmount)
{

}

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
