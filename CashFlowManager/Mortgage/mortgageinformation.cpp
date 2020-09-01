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
    updateMonthlyPayment();
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

void MortgageInformation::updateMonthlyPayment()
{
    monthlyPayment = totalLoanAmount * (monthlyInterestRate * pow((1.0 + monthlyInterestRate), (loanTerm * 12.0))) / (pow((1.0 + monthlyInterestRate), (loanTerm * 12.0)) - 1.0);
}

void MortgageInformation::setTotalLoanAmount(double amount)
{
    totalLoanAmount = amount;
    updateMonthlyPayment();
}

void MortgageInformation::setInterestRate(double rate)
{
    interestRate = rate;
    monthlyInterestRate = interestRate / 12.0;
    updateMonthlyPayment();
}

void MortgageInformation::setLoanTerm(int term)
{
    loanTerm = term;
    updateMonthlyPayment();
}

