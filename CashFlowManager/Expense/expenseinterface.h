#ifndef EXPENSEINTERFACE_H
#define EXPENSEINTERFACE_H

#include <set>
#include <string>
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
    virtual std::multiset<ExpenseTransaction*> getExpenseTransactionsByTimePeriod(const std::string& expenseType, const QDate& startingPeriod, const QDate& endingPeriod) const = 0;
    virtual double getExpenseTransactionsTotalByTimePeriod(const std::string& expenseType, const QDate& startingPeriod, const QDate& endingPeriod) const = 0;
    virtual std::vector<AutomaticMonthlyPayment*> getAutomaticMonthlyPayments() const = 0;
    virtual void addExpenseType(const ExpenseType& type) = 0;
    virtual void addExpenseTransactionByType(const std::string& expenseType, const ExpenseTransaction& transaction) = 0;
    virtual void addAutomaticMonthlyPayment(const AutomaticMonthlyPayment& payment) = 0;
    virtual double getMonthlyExpenses() const = 0;
    virtual double getMonthlyBudget() const = 0;
    virtual double getYearlyExpenses() const = 0;

};

#endif // EXPENSEINTERFACE_H
