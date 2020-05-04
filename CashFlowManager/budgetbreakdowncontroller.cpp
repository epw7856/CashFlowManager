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
    expenseTypes = localExpenseInterface.getExpenseTypes();
    investmentTypes = localInvestmentInterface.getInvestmentTypes();
}

std::string BudgetBreakdownController::getCurrentMonthAndYear() const
{
    return (DateUtilities::getCurrentMonth()) + " " + (DateUtilities::getCurrentYear());
}

std::string BudgetBreakdownController::getBudgetStatusStatement() const
{
    return CurrencyUtilities::formatCurrency(getTotalMonthlyExpenses()) + " of " + CurrencyUtilities::formatCurrency(getTotalMonthlyBudget());
}

double BudgetBreakdownController::getTotalMonthlyExpenses() const
{
    double total = 0.0;
    std::pair<QDate, QDate> dates = DateUtilities::getCurrentMonthDates();
    for(auto i : expenseTypes)
    {
        total += expenseInterface.getExpenseTransactionsTotalByTimePeriod(i->getName(), dates.first, dates.second);
    }
    return total;
}

double BudgetBreakdownController::getTotalMonthlyBudget() const
{
    double total = 0.0;
    for(auto i : expenseTypes)
    {
        total += i->getMonthlyBudget();
    }
    return total;
}

double BudgetBreakdownController::getTotalMonthlyInvestments() const
{
    double total = 0.0;
    std::pair<QDate, QDate> dates = DateUtilities::getCurrentMonthDates();
    for(auto i : investmentTypes)
    {
        total += investmentInterface.getInvestmentTransactionsTotalByTimePeriod(i->getName(), dates.first, dates.second);
    }
    return total;
}

double BudgetBreakdownController::getTotalMonthlyIncome() const
{
    std::pair<QDate, QDate> dates = DateUtilities::getCurrentMonthDates();
    return incomeInterface.getTotalIncomeTotalByTimePeriod(dates.first, dates.second);
}

double BudgetBreakdownController::getTotalYearlyExpenses() const
{
    double total = 0.0;
    std::pair<QDate, QDate> dates = DateUtilities::getCurrentYearDates();
    for(auto i : expenseTypes)
    {
        total += expenseInterface.getExpenseTransactionsTotalByTimePeriod(i->getName(), dates.first, dates.second);
    }
    return total;
}

double BudgetBreakdownController::getTotalYearlyIncome() const
{
    std::pair<QDate, QDate> dates = DateUtilities::getCurrentYearDates();
    return incomeInterface.getTotalIncomeTotalByTimePeriod(dates.first, dates.second);
}
