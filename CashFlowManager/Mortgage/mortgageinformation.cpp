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

void MortgageInformation::updateMarketValue(double value)
{
    marketValue = value;
}

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

const std::multiset<std::unique_ptr<MortgagePayment>>& MortgageInformation::getMortgagePayments() const
{
    return payments;
}

