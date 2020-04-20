#ifndef EXPENSEINTERFACE_H
#define EXPENSEINTERFACE_H

#include "expenseentry.h"
#include "expensetype.h"
#include <memory>
#include <set>
#include <vector>

class ExpenseInterface
{
public:
    virtual std::vector<std::shared_ptr<ExpenseType>> getExpenseTypes() const = 0;
    virtual std::set<std::shared_ptr<ExpenseEntry>> getExpenseList() const = 0;
    virtual std::set<std::shared_ptr<ExpenseEntry>> getExpenseListByTimePeriod(QDateTime period) const = 0;

};

#endif // EXPENSEINTERFACE_H
