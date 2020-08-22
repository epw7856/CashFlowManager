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
    virtual void deleteExpenseType(const std::string& expenseType) = 0;
    virtual void updateExpenseType(const std::string& currentName, const std::string& updatedName, double monthlyBudget) = 0;
    virtual std::vector<ExpenseTransaction*> getExpenseTransactionsByTimePeriod(const std::string& expenseType, const QDate& startingPeriod, const QDate& endingPeriod) const = 0;
    virtual double getExpenseTransactionsTotalByTimePeriod(const std::string& expenseType, const QDate& startingPeriod, const QDate& endingPeriod) const = 0;
    virtual std::vector<AutomaticMonthlyPayment*> getAutomaticMonthlyPayments() const = 0;
    virtual double getAutomaticMonthlyPaymentsTotal() const = 0;
    virtual void addExpenseType(const ExpenseType& type) = 0;
    virtual void addExpenseTransactionByType(const std::string& expenseType, const ExpenseTransaction& transaction) = 0;
    virtual void addAutomaticMonthlyPayment(const AutomaticMonthlyPayment& payment) = 0;
    virtual void deleteAutomaticMonthlyPayment(const AutomaticMonthlyPayment& payment) = 0;
    virtual void updateAutomaticMonthlyPayment(const AutomaticMonthlyPayment& existingPayment, const AutomaticMonthlyPayment& updatedPayment) = 0;
    virtual double getMonthlyExpenseTotal(int year, int month) const = 0;
    virtual double getMonthlyBudgetTotal(int month) const = 0;
    virtual double getYearlyExpenseTotal(int year) const = 0;
    virtual double getMonthlyBudgetByType(const std::string& expenseType, int month) const = 0;
};

#endif // EXPENSEINTERFACE_H
