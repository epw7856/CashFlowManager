#include "budgetbreakdowncontroller.h"
#include "currencyutilities.h"
#include "dateutilities.h"
#include "expenseinterface.h"
#include "expensetype.h"
#include "incomeinterface.h"
#include "investmentinterface.h"
#include "investmenttype.h"

BudgetBreakdownController::BudgetBreakdownController
(
    ExpenseInterface& localExpenseInterface,
    InvestmentInterface& localInvestmentInterface,
    IncomeInterface& localIncomeInterface
)
:
    expenseInterface(localExpenseInterface),
    investmentInterface(localInvestmentInterface),
    incomeInterface(localIncomeInterface)
{

}

std::string BudgetBreakdownController::getCurrentMonthAndYear() const
{
    return (DateUtilities::getCurrentMonth()) + " " + (DateUtilities::getCurrentYear());
}

std::string BudgetBreakdownController::getBudgetStatusStatement() const
{
    return CurrencyUtilities::formatCurrency(expenseInterface.getMonthlyExpenses()) + "  of  " + CurrencyUtilities::formatCurrency(expenseInterface.getMonthlyBudget());
}

double BudgetBreakdownController::getMonthlyExpenses() const
{
    return expenseInterface.getMonthlyExpenses();
}

double BudgetBreakdownController::getMonthlyBudget() const
{
    return expenseInterface.getMonthlyBudget();
}

double BudgetBreakdownController::getMonthlyInvestments() const
{
    return investmentInterface.getMonthlyInvestments();
}

double BudgetBreakdownController::getMonthlyIncome() const
{
    return incomeInterface.getMonthlyIncome();
}

double BudgetBreakdownController::getYearlyExpenses() const
{
    return expenseInterface.getYearlyExpenses();
}

double BudgetBreakdownController::getYearlyIncome() const
{
    return incomeInterface.getYearlyIncome();
}

double BudgetBreakdownController::getMonthlyBudgetSurplus() const
{
    return expenseInterface.getMonthlyBudget() - expenseInterface.getMonthlyExpenses();
}

double BudgetBreakdownController::getMonthlyCashSaved() const
{
    return (incomeInterface.getMonthlyIncome() -
            expenseInterface.getMonthlyExpenses() -
            investmentInterface.getMonthlyInvestments());
}

double BudgetBreakdownController::getYearlyAmountSaved() const
{
    return (incomeInterface.getYearlyIncome() - expenseInterface.getYearlyExpenses());
}

double BudgetBreakdownController::getYearlySavingsRatio() const
{
    double yearlyIncome = incomeInterface.getYearlyIncome();
    if(yearlyIncome > 0.0)
    {
        return (incomeInterface.getYearlyIncome() - expenseInterface.getYearlyExpenses()) / yearlyIncome;
    }
    else
    {
        return 0.0;
    }
}

double BudgetBreakdownController::getRemainingBudget() const
{
    double remaining = getMonthlyBudget() - getMonthlyExpenses();
    if(remaining < 0.0)
    {
        remaining = 0.0;
    }
    return remaining;
}
