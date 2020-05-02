#ifndef EXPENSETYPE_H
#define EXPENSETYPE_H

#include <set>
#include "transactioncomparison.h"

class ExpenseTransaction;
class QDate;

class ExpenseType
{
public:
    ExpenseType(std::string inputName, double inputBudget);
    std::string getName() const;
    double getMonthlyBudget() const;
    void addExpenseTransaction(const ExpenseTransaction& transaction);
    const std::multiset<std::unique_ptr<ExpenseTransaction>, TransactionComparison<ExpenseTransaction>>& getTransactionList() const;

private:
    std::string name = "";
    double monthlyBudget = 0.00;
    std::multiset<std::unique_ptr<ExpenseTransaction>, TransactionComparison<ExpenseTransaction>> expenseTransactionList;
};

inline std::string ExpenseType::getName() const
{
    return name;
}

inline double ExpenseType::getMonthlyBudget() const
{
    return monthlyBudget;
}

#endif // EXPENSETYPE_H
