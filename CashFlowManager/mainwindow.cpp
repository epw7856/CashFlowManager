#include "currencyutilities.h"
#include "dateutilities.h"
#include "mainwindow.h"
#include "mainwindowcontroller.h"
#include "systemdatasource.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
:
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    sds(std::make_unique<SystemDataSource>("../SystemConfiguration.json")),
    mainWindowController(std::make_unique<MainWindowController>(*sds)),
    expenseTableModel(*sds, QDate::currentDate().month(), false),
    investmentTableModel(*sds, QDate::currentDate().month(), false)
{
    ui->setupUi(this);
    ui->verticalLayout_8->setAlignment(Qt::AlignTop);
    ui->verticalLayout_10->setAlignment(Qt::AlignTop);
    ui->verticalLayout_11->setAlignment(Qt::AlignTop);
    expenseTableModel.setExpenseTypes();
    investmentTableModel.setInvestmentTypes();

    connect(ui->actionExit, &QAction::triggered, this, &MainWindow::onActionExitTriggered);
    connect(ui->actionYearly_Budget_Summary, &QAction::triggered, this, &MainWindow::onActionYearlyBudgetSummaryTriggered);
    connect(ui->actionMonthly_Budget_Summary, &QAction::triggered, this, &MainWindow::onActionMonthlyBudgetSummaryTriggered);

    updateDisplayedInformation();
}

MainWindow::~MainWindow()
{
    sds->saveSystemConfig();
    delete ui;
}

void MainWindow::onActionExitTriggered()
{
    close();
}

void MainWindow::onActionYearlyBudgetSummaryTriggered()
{
    mainWindowController->showYearlyBudgetSummaryDialog(this);
}

void MainWindow::onActionMonthlyBudgetSummaryTriggered()
{
    mainWindowController->showMonthlyBudgetSummaryDialog(this);
}

void MainWindow::onActionFoodExpensesTriggered()
{

}

void MainWindow::onActionMiscExpensesTriggered()
{

}

void MainWindow::updateDisplayedInformation()
{
    configureBudgetStatusBarChart();
    configureBreakdownPieChart();
    configureExpenseTableView();
    configureInvestmentTableView();

    ui->labelCurrentMonth->setText(QString::fromStdString(mainWindowController->getCurrentMonthAndYear()));
    ui->labelBudgetStatus->setText(QString::fromStdString(mainWindowController->getBudgetStatusStatement()));
    ui->labelMonthlyExpenses->setText(QString::fromStdString(CurrencyUtilities::formatCurrency(mainWindowController->getMonthlyExpenseTotal())));
    ui->labelMonthlyInvestments->setText(QString::fromStdString(CurrencyUtilities::formatCurrency(mainWindowController->getMonthlyInvestmentTotal())));
    ui->labelMonthlyIncome->setText(QString::fromStdString(CurrencyUtilities::formatCurrency(mainWindowController->getMonthlyIncomeTotal())));
    ui->labelMonthlyBudgetSurplus->setText(QString::fromStdString(CurrencyUtilities::formatCurrency(mainWindowController->getMonthlyBudgetSurplus())));
    ui->labelMonthlyCashSaved->setText(QString::fromStdString(CurrencyUtilities::formatCurrency(mainWindowController->getMonthlyCashSavedTotal())));
    ui->labelYearlyExpenses->setText(QString::fromStdString(CurrencyUtilities::formatCurrency(mainWindowController->getYearlyExpenseTotal())));
    ui->labelYearlyInvestments->setText(QString::fromStdString(CurrencyUtilities::formatCurrency(mainWindowController->getYearlyInvestmentTotal())));
    ui->labelYearlyIncome->setText(QString::fromStdString(CurrencyUtilities::formatCurrency(mainWindowController->getYearlyIncomeTotal())));
    ui->labelYearlyCashSaved->setText(QString::fromStdString(CurrencyUtilities::formatCurrency(mainWindowController->getYearlyCashSavedTotal())));
    ui->labelYearlySavingsRatio->setText(QString::fromStdString(CurrencyUtilities::formatRatio(mainWindowController->getYearlySavingsRatio())));
}

void MainWindow::configureBudgetStatusBarChart()
{
    QBarSet* expenses = new QBarSet("Expenses");
    QBarSet* remainingBudget = new QBarSet("Remaining Budget");
    *expenses << mainWindowController->getMonthlyExpenseTotal();
    *remainingBudget << mainWindowController->getMonthlyRemainingBudget();
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
    QPieSlice* expenseSlice = new QPieSlice("Expenses", mainWindowController->getYearlyExpenseTotal());
    expenseSlice->setBrush(Qt::red);
    QPieSlice* cashSlice = new QPieSlice("Cash", mainWindowController->getYearlyCashSavedTotal());
    cashSlice->setBrush(Qt::green);

    QPieSeries* series = new QPieSeries();
    series->append(expenseSlice);
    series->append(cashSlice);

    for(const auto& i : mainWindowController->getInvestmentTypesAndYearlyTotals())
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
    ui->tableViewMonthlyExpenses->setModel(&expenseTableModel);
    ui->tableViewMonthlyExpenses->setSelectionMode(QAbstractItemView::NoSelection);

    // Set bold font for the header
    QFont font(ui->tableViewMonthlyExpenses->font());
    font.setBold(true);
    ui->tableViewMonthlyExpenses->horizontalHeader()->setFont(font);

    // Disable horizontal scroll bar
    ui->tableViewMonthlyExpenses->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    // Disable cell resizing and selections
    ui->tableViewMonthlyExpenses->horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed);
    ui->tableViewMonthlyExpenses->horizontalHeader()->setFixedHeight(25);
    ui->tableViewMonthlyExpenses->verticalHeader()->setSectionResizeMode(QHeaderView::Fixed);
    ui->tableViewMonthlyExpenses->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableViewMonthlyExpenses->setFocusPolicy(Qt::NoFocus);
    ui->tableViewMonthlyExpenses->setSelectionMode(QAbstractItemView::NoSelection);

    // Add header frame
    //ui->tableViewMonthlyExpenses->horizontalHeader()->setFrameStyle(QFrame::HLine);
    //ui->tableViewMonthlyExpenses->horizontalHeader()->setFrameShadow(QFrame::Plain);
    //ui->tableViewMonthlyExpenses->horizontalHeader()->setLineWidth(1);

    // Resize columns to be uniform
    int maxColumnWidth = 0;
    for(int i = 1; i < expenseTableModel.columnCount(); ++i)
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
    ui->tableViewMonthlyExpenses->resizeRowsToContents();
    for(int i = 0; i < expenseTableModel.rowCount(); ++i)
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

    if(ui->tableViewMonthlyExpenses->verticalScrollBar()->width() < 100)
    {
        tableWidth += ui->tableViewMonthlyExpenses->verticalScrollBar()->width();
    }

    ui->tableViewMonthlyExpenses->setMinimumWidth(tableWidth);
    ui->tableViewMonthlyExpenses->setMaximumWidth(tableWidth);
}

void MainWindow::configureInvestmentTableView()
{
    // Add table model data and disable selection
    ui->tableViewMonthlyInvestments->setModel(&investmentTableModel);
    ui->tableViewMonthlyInvestments->setSelectionMode(QAbstractItemView::NoSelection);

    // Set bold font for the header
    QFont font(ui->tableViewMonthlyInvestments->font());
    font.setBold(true);
    ui->tableViewMonthlyInvestments->horizontalHeader()->setFont(font);

    // Disable horizontal scroll bar
    ui->tableViewMonthlyInvestments->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    // Disable cell resizing and selections
    ui->tableViewMonthlyInvestments->horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed);
    ui->tableViewMonthlyInvestments->horizontalHeader()->setFixedHeight(25);
    ui->tableViewMonthlyInvestments->verticalHeader()->setSectionResizeMode(QHeaderView::Fixed);
    ui->tableViewMonthlyInvestments->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableViewMonthlyInvestments->setFocusPolicy(Qt::NoFocus);
    ui->tableViewMonthlyInvestments->setSelectionMode(QAbstractItemView::NoSelection);

    // Add header frame
    //ui->tableViewMonthlyExpenses->horizontalHeader()->setFrameStyle(QFrame::HLine);
    //ui->tableViewMonthlyExpenses->horizontalHeader()->setFrameShadow(QFrame::Plain);
    //ui->tableViewMonthlyExpenses->horizontalHeader()->setLineWidth(1);

    // Resize columns to be uniform
    int maxColumnWidth = 0;
    for(int i = 1; i < investmentTableModel.columnCount(); ++i)
    {
        ui->tableViewMonthlyInvestments->resizeColumnToContents(i);
        int currentColumnWidth = ui->tableViewMonthlyInvestments->columnWidth(i);
        if(currentColumnWidth > maxColumnWidth)
        {
            maxColumnWidth = currentColumnWidth;
        }
    }

    ui->tableViewMonthlyInvestments->setColumnWidth(1, maxColumnWidth);
    ui->tableViewMonthlyInvestments->setColumnWidth(2, maxColumnWidth);
    ui->tableViewMonthlyInvestments->setColumnWidth(3, maxColumnWidth);

    // Set TableView height
    int tableHeight = 0;
    ui->tableViewMonthlyInvestments->resizeRowsToContents();
    for(int i = 0; i < investmentTableModel.rowCount(); ++i)
    {
        tableHeight += ui->tableViewMonthlyInvestments->rowHeight(i);
    }

    tableHeight += ui->tableViewMonthlyInvestments->horizontalHeader()->height();
    ui->tableViewMonthlyInvestments->setMaximumHeight(tableHeight+5);

    // Set TableView width
    int tableWidth = 0;
    for(int i = 0; i < ui->tableViewMonthlyInvestments->horizontalHeader()->count(); ++i)
    {
        tableWidth += ui->tableViewMonthlyInvestments->horizontalHeader()->sectionSize(i);
    }

    if(ui->tableViewMonthlyInvestments->verticalScrollBar()->width() < 100)
    {
        tableWidth += ui->tableViewMonthlyInvestments->verticalScrollBar()->width();
    }

    ui->tableViewMonthlyInvestments->setMinimumWidth(tableWidth);
    ui->tableViewMonthlyInvestments->setMaximumWidth(tableWidth);
}
