#ifndef MORTGAGEINFORMATION_H
#define MORTGAGEINFORMATION_H

#include <memory>
#include <QDate>
#include <set>
#include "transactioncomparison.h"

class MortgagePrincipalPayment;

class MortgageInformation
{
public:
    MortgageInformation
    (
        double loanAmount,
        double purchasePrice,
        double homeValue,
        double percentageRate,
        int term,
        QDate startDate
    );
    ~MortgageInformation();

    double getTotalLoanAmount() const;
    double getRemainingLoanBalance() const;
    double getPurchasePrice() const;
    double getMarketValue() const;
    double getInterestRate() const;
    int getLoanTerm() const;
    double getMonthlyPayment() const;
    QDate getLoanStartDate() const;
    const std::multiset<std::unique_ptr<MortgagePrincipalPayment>, TransactionComparison<MortgagePrincipalPayment>>& getPrincipalPayments() const;
    void updateMarketValue(double value);
    void updateRemainingBalance(double amount);
    void addPrincipalPayment(const MortgagePrincipalPayment& payment);

private:
    double totalLoanAmount = 0.0;
    double remainingLoanBalance = 0.0;
    double purchasePrice = 0.0;
    double marketValue = 0.0;
    double interestRate = 0.0;
    int loanTerm = 0;
    double monthlyPayment = 0.0;
    double monthlyInterestRate = 0.0;
    QDate loanStartDate;
    std::multiset<std::unique_ptr<MortgagePrincipalPayment>, TransactionComparison<MortgagePrincipalPayment>> principalPayments;
};

inline double MortgageInformation::getTotalLoanAmount() const
{
    return totalLoanAmount;
}

inline double MortgageInformation::getRemainingLoanBalance() const
{
    return remainingLoanBalance;
}

inline double MortgageInformation::getPurchasePrice() const
{
    return purchasePrice;
}

inline double MortgageInformation::getMarketValue() const
{
    return marketValue;
}

inline double MortgageInformation::getInterestRate() const
{
    return interestRate;
}

inline int MortgageInformation::getLoanTerm() const
{
    return loanTerm;
}

inline void MortgageInformation::updateMarketValue(double value)
{
    marketValue = value;
}

inline const std::multiset<std::unique_ptr<MortgagePrincipalPayment>, TransactionComparison<MortgagePrincipalPayment>>& MortgageInformation::getPrincipalPayments() const
{
    return principalPayments;
}

inline QDate MortgageInformation::getLoanStartDate() const
{
    return loanStartDate;
}

#endif // MORTGAGEINFORMATION_H
