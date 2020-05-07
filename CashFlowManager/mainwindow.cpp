#include "budgetbreakdowncontroller.h"
#include "currencyutilities.h"
#include "dateutilities.h"
#include "mainwindow.h"
#include "systemdatasource.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
:
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    sds(std::make_unique<SystemDataSource>("../SystemConfiguration.json")),
    budgetBreakdownController(std::make_unique<BudgetBreakdownController>(*sds, *sds, *sds)),
    tableModel(*sds, DateUtilities::getCurrentMonthDates())
{
    ui->setupUi(this);
    ui->tabBudgetBreakdown->setAutoFillBackground(true);
    tableModel.setExpenseTypes(sds->getExpenseTypes());

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
    configureExpenseTableView();

    ui->labelCurrentMonth->setText(QString::fromStdString(budgetBreakdownController->getCurrentMonthAndYear()));
    ui->labelBudgetStatus->setText(QString::fromStdString(budgetBreakdownController->getBudgetStatusStatement()));
    ui->labelMonthlyExpenses->setText(QString::fromStdString(CurrencyUtilities::formatCurrency(budgetBreakdownController->getMonthlyExpenseTotal())));
    ui->labelMonthlyInvestments->setText(QString::fromStdString(CurrencyUtilities::formatCurrency(budgetBreakdownController->getMonthlyInvestmentTotal())));
    ui->labelMonthlyIncome->setText(QString::fromStdString(CurrencyUtilities::formatCurrency(budgetBreakdownController->getMonthlyIncomeTotal())));
    ui->labelMonthlyBudgetSurplus->setText(QString::fromStdString(CurrencyUtilities::formatCurrency(budgetBreakdownController->getMonthlyBudgetSurplus())));
    ui->labelMonthlyCashSaved->setText(QString::fromStdString(CurrencyUtilities::formatCurrency(budgetBreakdownController->getMonthlyCashSavedTotal())));
    ui->labelYearlyExpenses->setText(QString::fromStdString(CurrencyUtilities::formatCurrency(budgetBreakdownController->getYearlyExpenseTotal())));
    ui->labelYearlyInvestments->setText(QString::fromStdString(CurrencyUtilities::formatCurrency(budgetBreakdownController->getYearlyInvestmentTotal())));
    ui->labelYearlyIncome->setText(QString::fromStdString(CurrencyUtilities::formatCurrency(budgetBreakdownController->getYearlyIncomeTotal())));
    ui->labelYearlyCashSaved->setText(QString::fromStdString(CurrencyUtilities::formatCurrency(budgetBreakdownController->getYearlyCashSavedTotal())));
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
    barChart->setMargins(QMargins(0,0,0,0));


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
    pieChart->setMargins(QMargins(0,0,0,0));

    ui->graphicsViewBreakdownPieChart->setChart(pieChart);
}

void MainWindow::configureExpenseTableView()
{
    // Add table model data and disable selection
    ui->tableViewMonthlyExpenses->setModel(&tableModel);
    ui->tableViewMonthlyExpenses->setSelectionMode(QAbstractItemView::NoSelection);

    // Set bold font for the header
    QFont font(ui->tableViewMonthlyExpenses->font());
    font.setBold(true);
    ui->tableViewMonthlyExpenses->horizontalHeader()->setFont(font);

    // Disable horizontal scroll bar
    ui->tableViewMonthlyExpenses->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    // Disable cell resizing and selections
    ui->tableViewMonthlyExpenses->horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed);
    ui->tableViewMonthlyExpenses->verticalHeader()->setSectionResizeMode(QHeaderView::Fixed);
    ui->tableViewMonthlyExpenses->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableViewMonthlyExpenses->setFocusPolicy(Qt::NoFocus);
    ui->tableViewMonthlyExpenses->setSelectionMode(QAbstractItemView::NoSelection);

    // Add header frame
    ui->tableViewMonthlyExpenses->horizontalHeader()->setFrameStyle(QFrame::HLine);
    ui->tableViewMonthlyExpenses->horizontalHeader()->setFrameShadow(QFrame::Plain);
    ui->tableViewMonthlyExpenses->horizontalHeader()->setLineWidth(1);

    // Resize columns to be uniform
    int maxColumnWidth = 0;
    for(int i = 1; i < tableModel.columnCount(); ++i)
    {
        ui->tableViewMonthlyExpenses->resizeColumnToContents(i);
        int currentColumnWidth = ui->tableViewMonthlyExpenses->columnWidth(i);
        if(currentColumnWidth > maxColumnWidth)
        {
            maxColumnWidth = currentColumnWidth;
        }
    }

    ui->tableViewMonthlyExpenses->setColumnWidth(1, maxColumnWidth);
    ui->tableViewMonthlyExpenses->setColumnWidth(2, maxColumnWidth);
    ui->tableViewMonthlyExpenses->setColumnWidth(3, maxColumnWidth);

    // Set TableView height
    int tableHeight = 0;
    for(int i = 0; i < tableModel.rowCount(); ++i)
    {
        tableHeight += ui->tableViewMonthlyExpenses->rowHeight(i);
    }

    tableHeight += ui->tableViewMonthlyExpenses->horizontalHeader()->height();
    ui->tableViewMonthlyExpenses->setMaximumHeight(tableHeight+5);

    // Set TableView width
    int tableWidth = 0;
    for(int i = 0; i < ui->tableViewMonthlyExpenses->horizontalHeader()->count(); ++i)
    {
        tableWidth += ui->tableViewMonthlyExpenses->horizontalHeader()->sectionSize(i);
    }

    if(ui->tableViewMonthlyExpenses->verticalScrollBar()->isVisible())
    {
        tableWidth += ui->tableViewMonthlyExpenses->verticalScrollBar()->width();
    }

    ui->tableViewMonthlyExpenses->setMinimumWidth(tableWidth+5);
    ui->tableViewMonthlyExpenses->setMaximumWidth(tableWidth+5);
}
