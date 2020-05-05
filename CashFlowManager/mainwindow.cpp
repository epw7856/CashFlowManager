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
    showMaximized();
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

    ui->labelCurrentMonth->setText(QString::fromStdString(budgetBreakdownController->getCurrentMonthAndYear()));
    ui->labelBudgetStatus->setText(QString::fromStdString(budgetBreakdownController->getBudgetStatusStatement()));
    ui->labelMonthlyExpenses->setText(QString::fromStdString(CurrencyUtilities::formatCurrency(budgetBreakdownController->getMonthlyExpenses())));
    ui->labelMonthlyInvestments->setText(QString::fromStdString(CurrencyUtilities::formatCurrency(budgetBreakdownController->getMonthlyInvestments())));
    ui->labelMonthlyIncome->setText(QString::fromStdString(CurrencyUtilities::formatCurrency(budgetBreakdownController->getMonthlyIncome())));
    ui->labelMonthlyBudgetSurplus->setText(QString::fromStdString(CurrencyUtilities::formatCurrency(budgetBreakdownController->getMonthlyBudgetSurplus())));
    ui->labelMonthlyCashSaved->setText(QString::fromStdString(CurrencyUtilities::formatCurrency(budgetBreakdownController->getMonthlyCashSaved())));
    ui->labelYearlyExpenses->setText(QString::fromStdString(CurrencyUtilities::formatCurrency(budgetBreakdownController->getYearlyExpenses())));
    ui->labelYearlyIncome->setText(QString::fromStdString(CurrencyUtilities::formatCurrency(budgetBreakdownController->getYearlyIncome())));
    ui->labelYearlySavings->setText(QString::fromStdString(CurrencyUtilities::formatCurrency(budgetBreakdownController->getYearlyAmountSaved())));
    ui->labelYearlySavingsRatio->setText(QString::fromStdString(CurrencyUtilities::formatRatio(budgetBreakdownController->getYearlySavingsRatio())));
}

void MainWindow::configureBudgetStatusBarChart()
{
    QBarSet* expenses = new QBarSet("Expenses");
    QBarSet* remainingBudget = new QBarSet("Remaining Budget");
    *expenses << budgetBreakdownController->getMonthlyExpenses();
    *remainingBudget << budgetBreakdownController->getRemainingBudget();
    expenses->setColor(QColorConstants::Red);
    remainingBudget->setColor(QColorConstants::Green);

    QHorizontalStackedBarSeries *series = new QHorizontalStackedBarSeries();
    series->append(expenses);
    series->append(remainingBudget);

    QChart* chart = new QChart();
    chart->addSeries(series);
    chart->setAnimationOptions(QChart::SeriesAnimations);
    chart->setBackgroundVisible(false);
    chart->legend()->setVisible(false);

    ui->graphicsViewExpenseBarChart->setChart(chart);
}

void MainWindow::configureBreakdownPieChart()
{

}
