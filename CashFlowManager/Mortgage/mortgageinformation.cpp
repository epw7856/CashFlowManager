#include "mortgageinformation.h"

MortgageInformation::MortgageInformation
(
    double loanAmount,
    double balance,
    double rate,
    std::multiset<std::unique_ptr<MortgagePayment>> paymentList
)
:
    totalLoanAmount(loanAmount),
    remainingLoanBalance(balance),
    interestRate(rate),
    payments(std::move(paymentList))
{

}

