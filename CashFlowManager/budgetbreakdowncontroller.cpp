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
    investmentTypes = investmentInterface.getInvestmentTypes();
}

std::string BudgetBreakdownController::getCurrentMonthAndYear() const
{
    return (DateUtilities::getCurrentMonth()) + " " + (DateUtilities::getCurrentYear());
}

std::string BudgetBreakdownController::getBudgetStatusStatement() const
{
    return CurrencyUtilities::formatCurrency(expenseInterface.getMonthlyExpenseTotal()) + "  of  " + CurrencyUtilities::formatCurrency(expenseInterface.getMonthlyBudgetTotal());
}

double BudgetBreakdownController::getMonthlyExpenseTotal() const
{
    return expenseInterface.getMonthlyExpenseTotal();
}

double BudgetBreakdownController::getMonthlyBudgetTotal() const
{
    return expenseInterface.getMonthlyBudgetTotal();
}

double BudgetBreakdownController::getMonthlyInvestmentTotal() const
{
    return investmentInterface.getMonthlyInvestmentTotal();
}

double BudgetBreakdownController::getMonthlyIncomeTotal() const
{
    return incomeInterface.getMonthlyIncomeTotal();
}

double BudgetBreakdownController::getYearlyExpenseTotal() const
{
    return expenseInterface.getYearlyExpenseTotal();
}

double BudgetBreakdownController::getYearlyIncomeTotal() const
{
    return incomeInterface.getYearlyIncomeTotal();
}

double BudgetBreakdownController::getYearlyCashSavedTotal() const
{
    return incomeInterface.getYearlyIncomeTotal() -
           expenseInterface.getYearlyExpenseTotal() -
           investmentInterface.getYearlyInvestmentTotal();
}

double BudgetBreakdownController::getMonthlyBudgetSurplus() const
{
    return expenseInterface.getMonthlyBudgetTotal() - expenseInterface.getMonthlyExpenseTotal();
}

double BudgetBreakdownController::getMonthlyCashSavedTotal() const
{
    return (incomeInterface.getMonthlyIncomeTotal() -
            expenseInterface.getMonthlyExpenseTotal() -
            investmentInterface.getMonthlyInvestmentTotal());
}

double BudgetBreakdownController::getYearlyAmountSaved() const
{
    return (incomeInterface.getYearlyIncomeTotal() - expenseInterface.getYearlyExpenseTotal());
}

double BudgetBreakdownController::getYearlySavingsRatio() const
{
    double yearlyIncome = incomeInterface.getYearlyIncomeTotal();
    if(yearlyIncome > 0.0)
    {
        return (incomeInterface.getYearlyIncomeTotal() - expenseInterface.getYearlyExpenseTotal()) / yearlyIncome;
    }
    else
    {
        return 0.0;
    }
}

double BudgetBreakdownController::getMonthlyRemainingBudget() const
{
    double remaining = expenseInterface.getMonthlyBudgetTotal() - expenseInterface.getMonthlyExpenseTotal();
    if(remaining < 0.0)
    {
        remaining = 0.0;
    }
    return remaining;
}

std::vector<std::pair<std::string, double>> BudgetBreakdownController::getInvestmentTypesAndYearlyTotals() const
{
    std::vector<std::pair<std::string, double>> types;
    std::pair<QDate, QDate> dates = DateUtilities::getCurrentYearDates();
    for(const auto& i : investmentInterface.getInvestmentTypes())
    {
        types.push_back({i->getName(), investmentInterface.getInvestmentTransactionsTotalByTimePeriod(i->getName(),dates.first, dates.second)});
    }

    return types;
}
