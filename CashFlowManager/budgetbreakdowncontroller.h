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
    double getTotalMonthlyExpenses() const;
    double getTotalMonthlyBudget() const;
    double getTotalMonthlyInvestments() const;
    double getTotalMonthlyIncome() const;
    double getTotalYearlyExpenses() const;
    double getTotalYearlyIncome() const;

private:
    ExpenseInterface& expenseInterface;
    InvestmentInterface& investmentInterface;
    IncomeInterface& incomeInterface;
    std::vector<ExpenseType*> expenseTypes;
    std::vector<InvestmentType*> investmentTypes;
};

#endif // BUDGETBREAKDOWNCONTROLLER_H
