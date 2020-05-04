#ifndef BUDGETBREAKDOWNCONTROLLER_H
#define BUDGETBREAKDOWNCONTROLLER_H

#include <string>
#include <vector>

class ExpenseInterface;
class ExpenseType;
class IncomeInterface;
class InvestmentInterface;
class InvestmentType;

class BudgetBreakdownController
{
public:
    BudgetBreakdownController(ExpenseInterface& localExpenseInterface,
                              InvestmentInterface& localInvestmentInterface,
                              IncomeInterface& localIncomeInterface);
    std::string getCurrentMonthAndYear() const;
    std::string getBudgetStatusStatement() const;
    std::string getMonthlyExpenses() const;
    std::string getMonthlyBudget() const;
    std::string getMonthlyInvestments() const;
    std::string getMonthlyIncome() const;
    std::string getYearlyExpenses() const;
    std::string getYearlyIncome() const;
    std::string getMonthlyBudgetSurplus() const;
    std::string getMonthlyCashSaved() const;
    std::string getYearlyAmountSaved() const;
    std::string getYearlySavingsRatio() const;

private:
    ExpenseInterface& expenseInterface;
    InvestmentInterface& investmentInterface;
    IncomeInterface& incomeInterface;
};

#endif // BUDGETBREAKDOWNCONTROLLER_H
