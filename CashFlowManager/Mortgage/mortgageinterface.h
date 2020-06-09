#ifndef MORTGAGEINTERFACE_H
#define MORTGAGEINTERFACE_H

class QDate;

class MortgageInterface
{
public:
    virtual ~MortgageInterface() = default;
    virtual double getTotalLoanAmount() const = 0;
    virtual double getPurchasePrice() const = 0;
    virtual double getMarketValue() const = 0;
    virtual double getInterestRate() const = 0;
    virtual int getLoanTerm() const = 0;
    virtual double getBasePayment() const = 0;
    virtual double getRemainingLoanBalance() const = 0;
    virtual QDate getLoanStartDate() const = 0;
    virtual double getAdditionalPrincipalPaymentTotalByDate(const QDate& startingPeriod, const QDate& endingPeriod) const = 0;
};

#endif // MORTGAGEINTERFACE_H
