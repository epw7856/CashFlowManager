#include "mortgageinformation.h"
#include "mortgagepayment.h"

MortgageInformation::MortgageInformation
(
    double loanAmount,
    double loanBalance,
    double purchasePrice,
    double homeValue,
    double percentageRate,
    int term
)
:
    totalLoanAmount(loanAmount),
    remainingLoanBalance(loanBalance),
    purchasePrice(purchasePrice),
    marketValue(homeValue),
    interestRate(percentageRate / 100.0),
    loanTerm(term)
{

}

MortgageInformation::~MortgageInformation() = default;

void MortgageInformation::updateRemainingBalance(double amount)
{
    remainingLoanBalance -= amount;
    if(remainingLoanBalance < 0.0)
    {
        remainingLoanBalance = 0.0;
    }
}

void MortgageInformation::addMortgagePayment(const MortgagePayment& payment)
{
    payments.insert(std::make_unique<MortgagePayment>(payment));
}



