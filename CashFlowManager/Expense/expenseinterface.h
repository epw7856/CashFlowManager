#ifndef EXPENSEINTERFACE_H
#define EXPENSEINTERFACE_H

#include <set>
#include <vector>

class AutomaticMonthlyPayment;
class ExpenseTransaction;
class ExpenseType;
class QDate;

class ExpenseInterface
{
public:
    virtual ~ExpenseInterface() = default;
    virtual std::vector<ExpenseType*> getExpenseTypes() const = 0;
    virtual std::multiset<ExpenseTransaction*> getExpenseTransactions() const = 0;
    virtual std::multiset<ExpenseTransaction*> getExpenseTransactionsByTimePeriod(QDate startingPeriod, QDate endingPeriod) const = 0;
    virtual std::vector<AutomaticMonthlyPayment*> getAutomaticMonthlyPayments() const = 0;
    virtual void addExpenseType(const ExpenseType& type) = 0;

};

#endif // EXPENSEINTERFACE_H
