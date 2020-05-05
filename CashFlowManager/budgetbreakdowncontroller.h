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
    double getMonthlyExpenses() const;
    double getMonthlyBudget() const;
    double getMonthlyInvestments() const;
    double getMonthlyIncome() const;
    double getYearlyExpenses() const;
    double getYearlyIncome() const;
    double getMonthlyBudgetSurplus() const;
    double getMonthlyCashSaved() const;
    double getYearlyAmountSaved() const;
    double getYearlySavingsRatio() const;
    double getRemainingBudget() const;

private:
    ExpenseInterface& expenseInterface;
    InvestmentInterface& investmentInterface;
    IncomeInterface& incomeInterface;
};

#endif // BUDGETBREAKDOWNCONTROLLER_H
