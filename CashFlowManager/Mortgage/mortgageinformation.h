#ifndef MORTGAGEINFORMATION_H
#define MORTGAGEINFORMATION_H

#include <memory>
#include <set>

class MortgagePayment;

class MortgageInformation
{
public:
    MortgageInformation
    (
        double loanAmount,
        double loanBalance,
        double purchasePrice,
        double homeValue,
        double percentageRate,
        int term
    );
    ~MortgageInformation();

    double getTotalLoanAmount() const;
    double getRemainingLoanBalance() const;
    double getPurchasePrice() const;
    double getMarketValue() const;
    double getInterestRate() const;
    int getLoanTerm() const;
    const std::multiset<std::unique_ptr<MortgagePayment>>& getMortgagePayments() const;
    void updateMarketValue(double value);
    void updateRemainingBalance(double amount);
    void addMortgagePayment(const MortgagePayment& payment);

private:
    double totalLoanAmount = 0.0;
    double remainingLoanBalance = 0.0;
    double purchasePrice = 0.0;
    double marketValue = 0.0;
    double interestRate = 0.0;
    int loanTerm = 0;
    std::multiset<std::unique_ptr<MortgagePayment>> payments;
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

inline const std::multiset<std::unique_ptr<MortgagePayment>>& MortgageInformation::getMortgagePayments() const
{
    return payments;
}

#endif // MORTGAGEINFORMATION_H
