#include "currencyutilities.h"
#include "dateutilities.h"
#include "expensetype.h"
#include "investmenttype.h"
#include "mainwindowcontroller.h"
#include "systemdatasource.h"
#include "yearlybudgetsummarydialog.h"
#include "yearlybudgetsummarydialogcontroller.h"

MainWindowController::MainWindowController(SystemDataSource& localSds) : sds(localSds) {}

MainWindowController::~MainWindowController() = default;

std::pair<QDate, QDate> MainWindowController::getCurrentMonthDates() const
{
    return DateUtilities::getCurrentMonthDates();
}

std::string MainWindowController::getCurrentMonthAndYear() const
{
    return (DateUtilities::getCurrentMonth()) + " " + (DateUtilities::getCurrentYear());
}

std::string MainWindowController::getBudgetStatusStatement() const
{
    return CurrencyUtilities::formatCurrency(sds.getMonthlyExpenseTotal()) + "  of  " + CurrencyUtilities::formatCurrency(sds.getMonthlyBudgetTotal());
}

double MainWindowController::getMonthlyExpenseTotal() const
{
    return sds.getMonthlyExpenseTotal();
}

double MainWindowController::getMonthlyBudgetTotal() const
{
    return sds.getMonthlyBudgetTotal();
}

double MainWindowController::getMonthlyInvestmentTotal() const
{
    return sds.getMonthlyInvestmentTotal();
}

double MainWindowController::getMonthlyIncomeTotal() const
{
    return sds.getMonthlyIncomeTotal();
}

double MainWindowController::getYearlyExpenseTotal() const
{
    return sds.getYearlyExpenseTotal();
}

double MainWindowController::getYearlyIncomeTotal() const
{
    return sds.getYearlyIncomeTotal();
}

double MainWindowController::getYearlyInvestmentTotal() const
{
    return sds.getYearlyInvestmentTotal();
}

double MainWindowController::getYearlyCashSavedTotal() const
{
    return sds.getYearlyIncomeTotal() -
           sds.getYearlyExpenseTotal() -
           sds.getYearlyInvestmentTotal();
}

double MainWindowController::getMonthlyBudgetSurplus() const
{
    return sds.getMonthlyBudgetTotal() - sds.getMonthlyExpenseTotal();
}

double MainWindowController::getMonthlyCashSavedTotal() const
{
    return (sds.getMonthlyIncomeTotal() -
            sds.getMonthlyExpenseTotal() -
            sds.getMonthlyInvestmentTotal());
}

double MainWindowController::getYearlyAmountSaved() const
{
    return (sds.getYearlyIncomeTotal() - sds.getYearlyExpenseTotal());
}

double MainWindowController::getYearlySavingsRatio() const
{
    double yearlyIncome = sds.getYearlyIncomeTotal();
    if(yearlyIncome > 0.0)
    {
        return (yearlyIncome - sds.getYearlyExpenseTotal()) / yearlyIncome;
    }
    else
    {
        return 0.0;
    }
}

double MainWindowController::getMonthlyRemainingBudget() const
{
    double remaining = sds.getMonthlyBudgetTotal() - sds.getMonthlyExpenseTotal();
    if(remaining < 0.0)
    {
        remaining = 0.0;
    }
    return remaining;
}

std::vector<std::pair<std::string, double>> MainWindowController::getInvestmentTypesAndYearlyTotals() const
{
    std::vector<std::pair<std::string, double>> types;
    for(const auto& i : sds.getInvestmentTypes())
    {
        types.push_back({i->getName(), sds.getYearlyInvestmentTotalByType(i->getName())});
    }

    return types;
}

void MainWindowController::showYearlyBudgetSummaryDialog(QWidget* parent)
{

}
