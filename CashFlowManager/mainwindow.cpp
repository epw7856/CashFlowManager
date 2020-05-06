#include "budgetbreakdowncontroller.h"
#include "currencyutilities.h"
#include "mainwindow.h"
#include "systemdatasource.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
:
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    sds(std::make_unique<SystemDataSource>("../SystemConfiguration.json"))
{
    budgetBreakdownController = std::make_unique<BudgetBreakdownController>(*sds, *sds, *sds);

    ui->setupUi(this);
    //showMaximized();
    ui->tabBudgetBreakdown->setAutoFillBackground(true);

    loadBudgetBreakdown();
}

MainWindow::~MainWindow()
{
    sds->saveSystemConfig();
    delete ui;
}

void MainWindow::loadBudgetBreakdown()
{
    configureBudgetStatusBarChart();
    configureBreakdownPieChart();

    ui->labelCurrentMonth->setText(QString::fromStdString(budgetBreakdownController->getCurrentMonthAndYear()));
    ui->labelBudgetStatus->setText(QString::fromStdString(budgetBreakdownController->getBudgetStatusStatement()));
    ui->labelMonthlyExpenses->setText(QString::fromStdString(CurrencyUtilities::formatCurrency(budgetBreakdownController->getMonthlyExpenseTotal())));
    ui->labelMonthlyInvestments->setText(QString::fromStdString(CurrencyUtilities::formatCurrency(budgetBreakdownController->getMonthlyInvestmentTotal())));
    ui->labelMonthlyIncome->setText(QString::fromStdString(CurrencyUtilities::formatCurrency(budgetBreakdownController->getMonthlyIncomeTotal())));
    ui->labelMonthlyBudgetSurplus->setText(QString::fromStdString(CurrencyUtilities::formatCurrency(budgetBreakdownController->getMonthlyBudgetSurplus())));
    ui->labelMonthlyCashSaved->setText(QString::fromStdString(CurrencyUtilities::formatCurrency(budgetBreakdownController->getMonthlyCashSavedTotal())));
    ui->labelYearlyExpenses->setText(QString::fromStdString(CurrencyUtilities::formatCurrency(budgetBreakdownController->getYearlyExpenseTotal())));
    ui->labelYearlyIncome->setText(QString::fromStdString(CurrencyUtilities::formatCurrency(budgetBreakdownController->getYearlyIncomeTotal())));
    ui->labelYearlySavings->setText(QString::fromStdString(CurrencyUtilities::formatCurrency(budgetBreakdownController->getYearlyAmountSaved())));
    ui->labelYearlySavingsRatio->setText(QString::fromStdString(CurrencyUtilities::formatRatio(budgetBreakdownController->getYearlySavingsRatio())));
}

void MainWindow::configureBudgetStatusBarChart()
{
    QBarSet* expenses = new QBarSet("Expenses");
    QBarSet* remainingBudget = new QBarSet("Remaining Budget");
    *expenses << budgetBreakdownController->getMonthlyExpenseTotal();
    *remainingBudget << budgetBreakdownController->getMonthlyRemainingBudget();
    expenses->setColor(QColorConstants::Red);
    remainingBudget->setColor(QColorConstants::Green);

    QHorizontalStackedBarSeries* stackedBarSeries = new QHorizontalStackedBarSeries();
    stackedBarSeries->append(expenses);
    stackedBarSeries->append(remainingBudget);

    QChart* barChart = new QChart();
    barChart->addSeries(stackedBarSeries);
    barChart->setAnimationOptions(QChart::SeriesAnimations);
    barChart->setBackgroundVisible(false);
    barChart->legend()->setVisible(false);

    ui->graphicsViewExpenseBarChart->setChart(barChart);
}

void MainWindow::configureBreakdownPieChart()
{
    QPieSlice* expenseSlice = new QPieSlice("Expenses", budgetBreakdownController->getYearlyExpenseTotal());
    expenseSlice->setBrush(Qt::red);
    QPieSlice* cashSlice = new QPieSlice("Cash", budgetBreakdownController->getYearlyCashSavedTotal());
    cashSlice->setBrush(Qt::green);

    QPieSeries* series = new QPieSeries();
    series->append(expenseSlice);
    series->append(cashSlice);

    for(const auto& i : budgetBreakdownController->getInvestmentTypesAndYearlyTotals())
    {
        series->append(QString::fromStdString(i.first), i.second);
    }

    QChart* pieChart = new QChart();
    pieChart->addSeries(series);
    pieChart->legend()->show();
    pieChart->legend()->setAlignment(Qt::AlignRight);
    pieChart->setBackgroundVisible(false);

    ui->graphicsViewBreakdownPieChart->setChart(pieChart);
}
