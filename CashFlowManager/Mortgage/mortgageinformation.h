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

    bool getMortgageInitialized() const;
    double getTotalLoanAmount() const;
    void setTotalLoanAmount(double amount);
    double getPurchasePrice() const;
    double getMarketValue() const;
    void setMarketValue(double value);
    double getInterestRate() const;
    void setInterestRate(double rate);
    int getLoanTerm() const;
    void setLoanTerm(int term);
    double getMonthlyPayment() const;
    QDate getLoanStartDate() const;
    void setLoanStartDate(QDate date);
    const std::multiset<std::unique_ptr<MortgagePrincipalPayment>, TransactionComparison<MortgagePrincipalPayment>>& getPrincipalPayments() const;
    void addPrincipalPayment(const MortgagePrincipalPayment& payment);

private:
    bool mortgageInitialized = false;
    double totalLoanAmount = 0.0;
    double purchasePrice = 0.0;
    double marketValue = 0.0;
    double interestRate = 0.0;
    int loanTerm = 0;
    double monthlyPayment = 0.0;
    double monthlyInterestRate = 0.0;
    QDate loanStartDate;
    std::multiset<std::unique_ptr<MortgagePrincipalPayment>, TransactionComparison<MortgagePrincipalPayment>> principalPayments;

    void updateMonthlyPayment();
    void updateMortgageInitialized();
};

inline bool MortgageInformation::getMortgageInitialized() const
{
    return mortgageInitialized;
}

inline double MortgageInformation::getTotalLoanAmount() const
{
    return totalLoanAmount;
}

inline double MortgageInformation::getPurchasePrice() const
{
    return purchasePrice;
}

inline double MortgageInformation::getMarketValue() const
{
    return marketValue;
}

inline void MortgageInformation::setMarketValue(double value)
{
    marketValue = value;
    updateMortgageInitialized();
}

inline double MortgageInformation::getInterestRate() const
{
    return interestRate;
}

inline int MortgageInformation::getLoanTerm() const
{
    return loanTerm;
}

inline const std::multiset<std::unique_ptr<MortgagePrincipalPayment>, TransactionComparison<MortgagePrincipalPayment>>& MortgageInformation::getPrincipalPayments() const
{
    return principalPayments;
}

inline QDate MortgageInformation::getLoanStartDate() const
{
    return loanStartDate;
}

inline void MortgageInformation::setLoanStartDate(QDate date)
{
    loanStartDate.setDate(date.year(), date.month(), date.day());
    updateMortgageInitialized();
}

inline double MortgageInformation::getMonthlyPayment() const
{
    return monthlyPayment;
}

#endif // MORTGAGEINFORMATION_H
