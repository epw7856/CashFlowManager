#include "addexpensetransactiondialog.h"
#include "addexpensetypedialog.h"
#include "addincometransactiondialog.h"
#include "addinvestmenttransactiondialog.h"
#include "addinvestmenttypedialog.h"
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
#include "updateassetinfodialog.h"
#include "updateautomaticmonthlypaymentsdialog.h"
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
    return (QDate::currentDate().toString("MMMM").toStdString()) + " " + (QDate::currentDate().toString("yyyy").toStdString());
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
    std::pair<QDate, QDate> dates = DateUtilities::getCurrentYearDates();
    return (sds.getYearlyIncomeTotal(currentYear) -
            sds.getYearlyExpenseTotal(currentYear) -
            sds.getYearlyInvestmentTotal(currentYear) -
            sds.getAdditionalPrincipalPaymentTotalByDate(dates.first, dates.second));
}

double MainWindowController::getMonthlyBudgetSurplus() const
{
    return sds.getMonthlyBudgetTotal(currentMonth) - sds.getMonthlyExpenseTotal(currentYear, currentMonth);
}

bool MainWindowController::isCurrentMonthOverBudget() const
{
    return (sds.getMonthlyExpenseTotal(currentYear, currentMonth) > sds.getMonthlyBudgetTotal(currentMonth));
}

double MainWindowController::getMonthlyAdditionalPrincipal() const
{
    std::pair<QDate, QDate> dates = DateUtilities::getCurrentMonthDates();
    return sds.getAdditionalPrincipalPaymentTotalByDate(dates.first, dates.second);
}

double MainWindowController::getMonthlyCashSavedTotal() const
{
    std::pair<QDate, QDate> dates = DateUtilities::getCurrentMonthDates();
    return (sds.getMonthlyIncomeTotal(currentYear, currentMonth) -
            sds.getMonthlyExpenseTotal(currentYear, currentMonth) -
            sds.getMonthlyInvestmentTotal(currentYear, currentMonth) -
            sds.getAdditionalPrincipalPaymentTotalByDate(dates.first, dates.second));
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

double MainWindowController::getYearlyAdditionalPrincipal() const
{
    std::pair<QDate, QDate> dates = DateUtilities::getCurrentYearDates();
    return sds.getAdditionalPrincipalPaymentTotalByDate(dates.first, dates.second);
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

std::string MainWindowController::getRatioForPieChart(double amount) const
{
    return CurrencyUtilities::formatRatio(amount / getYearlyIncomeTotal());
}

double MainWindowController::getYearlyExpenditureRatio() const
{
    std::pair<QDate, QDate> dates = DateUtilities::getCurrentYearDates();
    double totalExpenditures = sds.getYearlyExpenseTotal(currentYear) +
                               sds.getYearlyInvestmentTotal(currentYear) +
                               sds.getAdditionalPrincipalPaymentTotalByDate(dates.first, dates.second);

    return totalExpenditures / getYearlyIncomeTotal();
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

void MainWindowController::showAddExpenseTransactionDialog(QWidget* parent)
{
    if(addExpenseTransactionDialog == nullptr)
    {
        addExpenseTransactionDialog = std::make_unique<AddExpenseTransactionDialog>(sds, sds, parent);
    }

    connect(addExpenseTransactionDialog.get(), &AddExpenseTransactionDialog::dialogClosed, this, &MainWindowController::dialogCloseEvent);

    addExpenseTransactionDialog->show();
    addExpenseTransactionDialog->raise();
    addExpenseTransactionDialog->activateWindow();
}

void MainWindowController::showAddExpenseTypeDialog(QWidget* parent)
{
    if(addExpenseTypeDialog == nullptr)
    {
        addExpenseTypeDialog = std::make_unique<AddExpenseTypeDialog>(sds, sds, false, parent);
    }

    connect(addExpenseTypeDialog.get(), &AddExpenseTypeDialog::dialogClosed, this, &MainWindowController::dialogCloseEvent);

    addExpenseTypeDialog->show();
    addExpenseTypeDialog->raise();
    addExpenseTypeDialog->activateWindow();
}

void MainWindowController::showModifyExpenseTypeDialog(QWidget *parent)
{
    if(modifyExpenseTypeDialog == nullptr)
    {
        modifyExpenseTypeDialog = std::make_unique<AddExpenseTypeDialog>(sds, sds, true, parent);
    }

    connect(modifyExpenseTypeDialog.get(), &AddExpenseTypeDialog::dialogClosed, this, &MainWindowController::dialogCloseEvent);

    modifyExpenseTypeDialog->show();
    modifyExpenseTypeDialog->raise();
    modifyExpenseTypeDialog->activateWindow();
}

void MainWindowController::showAddInvestmentTransactionDialog(QWidget *parent)
{
    if(addInvestmentTransactionDialog == nullptr)
    {
        addInvestmentTransactionDialog = std::make_unique<AddInvestmentTransactionDialog>(sds, parent);
    }

    connect(addInvestmentTransactionDialog.get(), &AddInvestmentTransactionDialog::dialogClosed, this, &MainWindowController::dialogCloseEvent);

    addInvestmentTransactionDialog->show();
    addInvestmentTransactionDialog->raise();
    addInvestmentTransactionDialog->activateWindow();
}

void MainWindowController::showAddInvestmentTypeDialog(QWidget *parent)
{
    if(addInvestmentTypeDialog == nullptr)
    {
        addInvestmentTypeDialog = std::make_unique<AddInvestmentTypeDialog>(sds, false, parent);
    }

    connect(addInvestmentTypeDialog.get(), &AddInvestmentTypeDialog::dialogClosed, this, &MainWindowController::dialogCloseEvent);

    addInvestmentTypeDialog->show();
    addInvestmentTypeDialog->raise();
    addInvestmentTypeDialog->activateWindow();
}

void MainWindowController::showModifyInvestmentTypeDialog(QWidget *parent)
{
    if(modifyInvestmentTypeDialog == nullptr)
    {
        modifyInvestmentTypeDialog = std::make_unique<AddInvestmentTypeDialog>(sds, true, parent);
    }

    connect(modifyInvestmentTypeDialog.get(), &AddInvestmentTypeDialog::dialogClosed, this, &MainWindowController::dialogCloseEvent);

    modifyInvestmentTypeDialog->show();
    modifyInvestmentTypeDialog->raise();
    modifyInvestmentTypeDialog->activateWindow();
}

void MainWindowController::showAddIncomeTransactionDialog(QWidget *parent)
{
    if(addIncomeTransactionDialog == nullptr)
    {
        addIncomeTransactionDialog = std::make_unique<AddIncomeTransactionDialog>(sds, parent);
    }

    connect(addIncomeTransactionDialog.get(), &AddIncomeTransactionDialog::dialogClosed, this, &MainWindowController::dialogCloseEvent);

    addIncomeTransactionDialog->show();
    addIncomeTransactionDialog->raise();
    addIncomeTransactionDialog->activateWindow();
}

void MainWindowController::showUpdateAutomaticMonthlyPaymentDialog(QWidget *parent)
{
    if(updateAutomaticMonthlyPaymentsDialog == nullptr)
    {
        updateAutomaticMonthlyPaymentsDialog = std::make_unique<UpdateAutomaticMonthlyPaymentsDialog>(sds, parent);
    }

    connect(updateAutomaticMonthlyPaymentsDialog.get(), &UpdateAutomaticMonthlyPaymentsDialog::dialogClosed, this, &MainWindowController::dialogCloseEvent);

    updateAutomaticMonthlyPaymentsDialog->show();
    updateAutomaticMonthlyPaymentsDialog->raise();
    updateAutomaticMonthlyPaymentsDialog->activateWindow();
}

void MainWindowController::showUpdateAssetInfoDialog(QWidget *parent)
{
    if(updateAssetInfoDialog == nullptr)
    {
        updateAssetInfoDialog = std::make_unique<UpdateAssetInfoDialog>(sds, parent);
    }

    connect(updateAssetInfoDialog.get(), &UpdateAssetInfoDialog::dialogClosed, this, &MainWindowController::dialogCloseEvent);

    updateAssetInfoDialog->show();
    updateAssetInfoDialog->raise();
    updateAssetInfoDialog->activateWindow();
}

void MainWindowController::dialogCloseEvent()
{
    emit requestMainWindowUpdate();
}
