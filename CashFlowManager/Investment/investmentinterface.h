#ifndef INVESTMENTINTERFACE_H
#define INVESTMENTINTERFACE_H

#include <set>
#include <vector>

class QDate;
class InvestmentType;
class InvestmentTransaction;

class InvestmentInterface
{
public:
    virtual ~InvestmentInterface() = default;
    virtual std::vector<InvestmentType*> getInvestmentTypes() const = 0;
    virtual std::multiset<InvestmentTransaction*> getInvestmentTransactions() const = 0;
    virtual std::multiset<InvestmentTransaction*> getInvestmentTransactionsByTimePeriod(QDate startingPeriod, QDate endingPeriod) const = 0;
    virtual void addInvestmentType(const InvestmentType& type) = 0;
    virtual void addInvestmentTransaction(const InvestmentTransaction& transaction) = 0;
};

#endif // INVESTMENTINTERFACE_H
