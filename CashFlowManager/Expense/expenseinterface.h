#ifndef EXPENSEINTERFACE_H
#define EXPENSEINTERFACE_H

#include "expensetransaction.h"
#include "expensetype.h"
#include <set>
#include <vector>

class ExpenseInterface
{
public:
    virtual std::vector<ExpenseType> getExpenseTypes() const = 0;
    virtual std::set<ExpenseTransaction> getExpenseTransactions() const = 0;
    virtual std::set<ExpenseTransaction> getExpenseTransactionsByTimePeriod(QDate startingPeriod, QDate endingPeriod) const = 0;

};

#endif // EXPENSEINTERFACE_H
