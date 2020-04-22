#ifndef EXPENSEINTERFACE_H
#define EXPENSEINTERFACE_H

#include "automaticmonthlypayment.h"
#include "expensetransaction.h"
#include "expensetype.h"
#include <set>
#include <vector>

class ExpenseInterface
{
public:
    virtual std::vector<ExpenseType> getExpenseTypes() const = 0;
    virtual std::multiset<ExpenseTransaction> getExpenseTransactions() const = 0;
    virtual std::multiset<ExpenseTransaction> getExpenseTransactionsByTimePeriod(QDate startingPeriod, QDate endingPeriod) const = 0;
    virtual std::vector<AutomaticMonthlyPayment> getAutomaticMonthlyPayments() const = 0;

};

#endif // EXPENSEINTERFACE_H
