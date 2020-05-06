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
    double getMonthlyExpenseTotal() const;
    double getMonthlyBudgetTotal() const;
    double getMonthlyInvestmentTotal() const;
    double getMonthlyIncomeTotal() const;
    double getMonthlyCashSavedTotal() const;
    double getMonthlyBudgetSurplus() const;
    double getYearlyExpenseTotal() const;
    double getYearlyIncomeTotal() const;
    double getYearlyInvestmentTotal() const;
    double getYearlyCashSavedTotal() const;
    double getYearlyAmountSaved() const;
    double getYearlySavingsRatio() const;
    double getMonthlyRemainingBudget() const;
    std::vector<std::pair<std::string, double>> getInvestmentTypesAndYearlyTotals() const;

private:
    ExpenseInterface& expenseInterface;
    InvestmentInterface& investmentInterface;
    IncomeInterface& incomeInterface;
    std::vector<InvestmentType*> investmentTypes;
};

#endif // BUDGETBREAKDOWNCONTROLLER_H
