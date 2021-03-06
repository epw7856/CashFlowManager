#ifndef MORTGAGEINTERFACE_H
#define MORTGAGEINTERFACE_H

class QDate;
class MortgagePrincipalPayment;

class MortgageInterface
{
public:
    virtual ~MortgageInterface() = default;
    virtual bool mortgageExists() const = 0;
    virtual double getTotalLoanAmount() const = 0;
    virtual void updateTotalLoanAmount(double amount) = 0;
    virtual double getPurchasePrice() const = 0;
    virtual double getMarketValue() const = 0;
    virtual void updateMarketValue(double amount) = 0;
    virtual double getInterestRate() const = 0;
    virtual void updateInterestRate(double rate) = 0;
    virtual int getLoanTerm() const = 0;
    virtual void updateLoanTerm(int term) = 0;
    virtual double getBasePayment() const = 0;
    virtual QDate getLoanStartDate() const = 0;
    virtual void updateLoanStartDate(QDate date) = 0;
    virtual double getAdditionalPrincipalPaymentTotalByDate(const QDate& startingPeriod, const QDate& endingPeriod) const = 0;
    virtual bool mortgagePaidForMonth(int year, int month) const = 0;
    virtual void addAdditionalPrincipalPayment(const MortgagePrincipalPayment& payment) = 0;
};

#endif // MORTGAGEINTERFACE_H
