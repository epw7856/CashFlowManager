#include "assetsummarydialog.h"
#include "automaticmonthlypaymentsummarydialog.h"
#include "currencyutilities.h"
#include "dateutilities.h"
#include "expensetype.h"
#include "expensetypesummarydialog.h"
#include "investmenttype.h"
#include "mainwindowcontroller.h"
#include "monthlybudgetsummarydialog.h"
#include "mortgagesummarydialog.h"
#include "systemdatasource.h"
#include "yearlybudgetsummarydialog.h"
#include "yearlyincomesummarydialog.h"

MainWindowController::MainWindowController(SystemDataSource& localSds)
:
    sds(localSds)
{
    currentYear = QDate::currentDate().year();
    currentMonth = QDate::currentDate().month();
}

MainWindowController::~MainWindowController() = default;

std::string MainWindowController::getCurrentMonthAndYear() const
{
    return (DateUtilities::getCurrentMonth()) + " " + (DateUtilities::getCurrentYear());
}

std::string MainWindowController::getBudgetStatusStatement() const
{
    return CurrencyUtilities::formatCurrency(sds.getMonthlyExpenseTotal(currentYear, currentMonth)) + "  of  " + CurrencyUtilities::formatCurrency(sds.getMonthlyBudgetTotal(currentMonth));
}

double MainWindowController::getMonthlyExpenseTotal() const
{
    return sds.getMonthlyExpenseTotal(currentYear, currentMonth);
}

double MainWindowController::getMonthlyBudgetTotal() const
{
    return sds.getMonthlyBudgetTotal(currentMonth);
}

double MainWindowController::getMonthlyInvestmentTotal() const
{
    return sds.getMonthlyInvestmentTotal(currentYear, currentMonth);
}

double MainWindowController::getMonthlyIncomeTotal() const
{
    return sds.getMonthlyIncomeTotal(currentYear, currentMonth);
}

double MainWindowController::getYearlyExpenseTotal() const
{
    return sds.getYearlyExpenseTotal(currentYear);
}

double MainWindowController::getYearlyIncomeTotal() const
{
    return sds.getYearlyIncomeTotal(currentYear);
}

double MainWindowController::getYearlyInvestmentTotal() const
{
    return sds.getYearlyInvestmentTotal(currentYear);
}

double MainWindowController::getYearlyCashSavedTotal() const
{
    return sds.getYearlyIncomeTotal(currentYear) -
           sds.getYearlyExpenseTotal(currentYear) -
           sds.getYearlyInvestmentTotal(currentYear);
}

double MainWindowController::getMonthlyBudgetSurplus() const
{
    return sds.getMonthlyBudgetTotal(currentMonth) - sds.getMonthlyExpenseTotal(currentYear, currentMonth);
}

double MainWindowController::getMonthlyCashSavedTotal() const
{
    return (sds.getMonthlyIncomeTotal(currentYear, currentMonth) -
            sds.getMonthlyExpenseTotal(currentYear, currentMonth) -
            sds.getMonthlyInvestmentTotal(currentYear, currentMonth));
}

double MainWindowController::getYearlyAmountSaved() const
{
    return (sds.getYearlyIncomeTotal(currentYear) - sds.getYearlyExpenseTotal(currentYear));
}

double MainWindowController::getYearlySavingsRatio() const
{
    double yearlyIncome = sds.getYearlyIncomeTotal(currentYear);
    if(yearlyIncome > 0.0)
    {
        return (yearlyIncome - sds.getYearlyExpenseTotal(currentYear)) / yearlyIncome;
    }
    else
    {
        return 0.0;
    }
}

double MainWindowController::getMonthlyRemainingBudget() const
{
    double remaining = sds.getMonthlyBudgetTotal(currentMonth) - sds.getMonthlyExpenseTotal(currentYear, currentMonth);
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
        std::pair<QDate, QDate> dates = DateUtilities::getYearlyDates(currentYear);
        types.push_back({i->getName(), sds.getInvestmentTransactionsTotalByTimePeriod(i->getName(), dates.first, dates.second)});
    }

    return types;
}

void MainWindowController::showYearlyBudgetSummaryDialog(QWidget* parent)
{
    if(yearlyBudgetDialog == nullptr)
    {
        yearlyBudgetDialog = std::make_unique<YearlyBudgetSummaryDialog>(sds, sds, parent);
    }

    yearlyBudgetDialog->show();
    yearlyBudgetDialog->raise();
    yearlyBudgetDialog->activateWindow();
}

void MainWindowController::showMonthlyBudgetSummaryDialog(QWidget* parent)
{
    if(monthlyBudgetDialog == nullptr)
    {
        monthlyBudgetDialog = std::make_unique<MonthlyBudgetSummaryDialog>(sds, sds, parent);
    }

    monthlyBudgetDialog->show();
    monthlyBudgetDialog->raise();
    monthlyBudgetDialog->activateWindow();
}

void MainWindowController::showFoodExpensesDialog(QWidget* parent)
{
    if(foodExpensesDialog == nullptr)
    {
        foodExpensesDialog = std::make_unique<ExpenseTypeSummaryDialog>(sds, "Food", parent);
    }

    foodExpensesDialog->show();
    foodExpensesDialog->raise();
    foodExpensesDialog->activateWindow();
}

void MainWindowController::showMiscExpensesDialog(QWidget* parent)
{
    if(miscExpensesDialog == nullptr)
    {
        miscExpensesDialog = std::make_unique<ExpenseTypeSummaryDialog>(sds, "Misc", parent);
    }

    miscExpensesDialog->show();
    miscExpensesDialog->raise();
    miscExpensesDialog->activateWindow();
}

void MainWindowController::showYearlyIncomeSummaryDialog(QWidget* parent)
{
    if(yearlyIncomeDialog == nullptr)
    {
        yearlyIncomeDialog = std::make_unique<YearlyIncomeSummaryDialog>(sds, parent);
    }

    yearlyIncomeDialog->show();
    yearlyIncomeDialog->raise();
    yearlyIncomeDialog->activateWindow();
}

void MainWindowController::showAutomaticMonthlyPaymentSummaryDialog(QWidget *parent)
{
    if(automaticMonthlyPaymentDialog == nullptr)
    {
        automaticMonthlyPaymentDialog = std::make_unique<AutomaticMonthlyPaymentSummaryDialog>(sds, parent);
    }

    automaticMonthlyPaymentDialog->show();
    automaticMonthlyPaymentDialog->raise();
    automaticMonthlyPaymentDialog->activateWindow();
}

void MainWindowController::showAssetSummaryDialog(QWidget* parent)
{
    if(assetSummaryDialog == nullptr)
    {
        assetSummaryDialog = std::make_unique<AssetSummaryDialog>(sds, parent);
    }

    assetSummaryDialog->show();
    assetSummaryDialog->raise();
    assetSummaryDialog->activateWindow();
}

void MainWindowController::showMortgageSummaryDialog(QWidget* parent)
{
    if(mortgageSummaryDialog == nullptr)
    {
        mortgageSummaryDialog = std::make_unique<MortgageSummaryDialog>(sds, parent);
    }

    mortgageSummaryDialog->show();
    mortgageSummaryDialog->raise();
    mortgageSummaryDialog->activateWindow();
}
