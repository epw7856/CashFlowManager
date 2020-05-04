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
    return CurrencyUtilities::formatCurrency(expenseInterface.getMonthlyExpenses()) + " of " + CurrencyUtilities::formatCurrency(expenseInterface.getMonthlyBudget());
}

std::string BudgetBreakdownController::getMonthlyExpenses() const
{
    return CurrencyUtilities::formatCurrency(expenseInterface.getMonthlyExpenses());
}

std::string BudgetBreakdownController::getMonthlyBudget() const
{
    return CurrencyUtilities::formatCurrency(expenseInterface.getMonthlyBudget());
}

std::string BudgetBreakdownController::getMonthlyInvestments() const
{
    return CurrencyUtilities::formatCurrency(investmentInterface.getMonthlyInvestments());
}

std::string BudgetBreakdownController::getMonthlyIncome() const
{
    return CurrencyUtilities::formatCurrency(incomeInterface.getMonthlyIncome());
}

std::string BudgetBreakdownController::getYearlyExpenses() const
{
    return CurrencyUtilities::formatCurrency(expenseInterface.getYearlyExpenses());
}

std::string BudgetBreakdownController::getYearlyIncome() const
{
    return CurrencyUtilities::formatCurrency(incomeInterface.getYearlyIncome());
}

std::string BudgetBreakdownController::getMonthlyBudgetSurplus() const
{
    return CurrencyUtilities::formatCurrency((expenseInterface.getMonthlyBudget() - expenseInterface.getMonthlyExpenses()));
}

std::string BudgetBreakdownController::getMonthlyCashSaved() const
{
    return CurrencyUtilities::formatCurrency((incomeInterface.getMonthlyIncome() -
                                              expenseInterface.getMonthlyExpenses() -
                                              investmentInterface.getMonthlyInvestments()));
}

std::string BudgetBreakdownController::getYearlyAmountSaved() const
{
    return CurrencyUtilities::formatCurrency((incomeInterface.getYearlyIncome() - expenseInterface.getYearlyExpenses()));
}

std::string BudgetBreakdownController::getYearlySavingsRatio() const
{
    double yearlyIncome = incomeInterface.getYearlyIncome();
    if(yearlyIncome > 0.0)
    {
        return CurrencyUtilities::formatRatio((incomeInterface.getYearlyIncome() - expenseInterface.getYearlyExpenses()) / yearlyIncome);
    }
    else
    {
        return CurrencyUtilities::formatRatio(0.0);
    }
}
