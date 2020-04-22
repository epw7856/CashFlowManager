#ifndef INVESTMENTINTERFACE_H
#define INVESTMENTINTERFACE_H

#include "investmenttransaction.h"
#include "investmenttype.h"
#include <set>

class InvestmentInterface
{
    virtual std::vector<InvestmentType> getInvestmentTypes() const = 0;
    virtual std::multiset<InvestmentTransaction> getInvestmentTransactions() const = 0;
    virtual std::multiset<InvestmentTransaction> getInvestmentTransactionsByTimePeriod(QDate startingPeriod, QDate endingPeriod) const = 0;
};

#endif // INVESTMENTINTERFACE_H
