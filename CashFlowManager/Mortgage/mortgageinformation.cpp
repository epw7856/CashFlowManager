#include <cmath>
#include "mortgageinformation.h"
#include "mortgageprincipalpayment.h"

MortgageInformation::MortgageInformation
(
    double loanAmount,
    double purchasePrice,
    double homeValue,
    double percentageRate,
    int term,
    QDate startDate
)
:
    totalLoanAmount(loanAmount),
    purchasePrice(purchasePrice),
    marketValue(homeValue),
    interestRate(percentageRate / 100.0),
    loanTerm(term),
    monthlyInterestRate(interestRate / 12.0),
    loanStartDate(startDate)
{
    monthlyPayment = totalLoanAmount * (monthlyInterestRate * pow((1 + monthlyInterestRate), (loanTerm * 12.0))) / (pow((1 + monthlyInterestRate), (loanTerm * 12.0)) - 1);
}

double MortgageInformation::getMonthlyPayment() const
{
    return monthlyPayment;
}

MortgageInformation::~MortgageInformation() = default;

void MortgageInformation::addPrincipalPayment(const MortgagePrincipalPayment& payment)
{
    principalPayments.insert(std::make_unique<MortgagePrincipalPayment>(payment));
}
