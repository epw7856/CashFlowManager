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
    void updateName(const std::string& updatedName);
    void updateBudget(double updatedAmount);
    std::string getName() const;
    double getMonthlyBudget() const;
    bool getVariableExpenseFlag() const;
    void addExpenseTransaction(const ExpenseTransaction& transaction);
    const std::multiset<std::unique_ptr<ExpenseTransaction>, TransactionComparison<ExpenseTransaction>>& getTransactionList() const;

private:
    std::string name = "";
    double monthlyBudget = 0.00;
    bool variableExpenseFlag = false;
    std::multiset<std::unique_ptr<ExpenseTransaction>, TransactionComparison<ExpenseTransaction>> expenseTransactionList;
};

inline void ExpenseType::updateName(const std::string& updatedName)
{
    name = updatedName;
}

inline void ExpenseType::updateBudget(double updatedAmount)
{
    monthlyBudget = updatedAmount;
    variableExpenseFlag = (monthlyBudget == 0.0);
}

inline std::string ExpenseType::getName() const
{
    return name;
}

inline double ExpenseType::getMonthlyBudget() const
{
    return monthlyBudget;
}

inline bool ExpenseType::getVariableExpenseFlag() const
{
    return variableExpenseFlag;
}

#endif // EXPENSETYPE_H
