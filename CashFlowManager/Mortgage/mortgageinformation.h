#ifndef MORTGAGEINFORMATION_H
#define MORTGAGEINFORMATION_H

#include <memory>
#include "mortgagepayment.h"
#include <set>

class MortgageInformation
{
public:
    MortgageInformation
    (
        double loanAmount,
        double balance,
        double rate,
        std::multiset<std::unique_ptr<MortgagePayment>> paymentList
    );

private:
    double totalLoanAmount = 0.0;
    double remainingLoanBalance = 0.0;
    double interestRate = 0.0;
    std::multiset<std::unique_ptr<MortgagePayment>> payments = {};

};

#endif // MORTGAGEINFORMATION_H
