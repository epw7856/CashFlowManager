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
    sds(std::make_unique<SystemDataSource>()),
    mainWindowController(std::make_unique<MainWindowController>(*sds)),
    expenseTableModel(*sds, QDate::currentDate().month(), false),
    investmentTableModel(*sds, QDate::currentDate().month(), false)
{
    ui->setupUi(this);
    ui->verticalLayoutMonthlyBreakdown->setAlignment(Qt::AlignTop);
    ui->verticalLayoutMonthlyExpenseBudget->setAlignment(Qt::AlignTop);
    ui->verticalLayoutMonthlyInvestmentBudget->setAlignment(Qt::AlignTop);
    ui->verticalLayoutYearlyBreakdown->setAlignment(Qt::AlignTop);
    ui->verticalLayoutYearlyIncomeDistribution->setAlignment(Qt::AlignTop);
    ui->tabWidget->setAutoFillBackground(true);
    ui->tabWidget->setStyleSheet("background-color: rgb(240, 240, 240);");
    ui->tabWidget->setCurrentIndex(0);

    connect(ui->actionExit, &QAction::triggered, this, &MainWindow::onActionExitTriggered);
    connect(ui->actionYearlyBudgetSummary, &QAction::triggered, this, &MainWindow::onActionYearlyBudgetSummaryTriggered);
    connect(ui->actionMonthlyBudgetSummaryExpenseType, &QAction::triggered, this, &MainWindow::onActionMonthlyBudgetExpenseTypeSummaryTriggered);
    connect(ui->actionMonthlyBudgetSummary, &QAction::triggered, this, &MainWindow::onActionMonthlyBudgetSummaryTriggered);
    connect(ui->actionYearlyIncomeSummary, &QAction::triggered, this, &MainWindow::onActionYearlyIncomeSummaryTriggered);
    connect(ui->actionAutomaticMonthlyPayments, &QAction::triggered, this, &MainWindow::onActionAutomaticMonthlyPaymentSummaryTriggered);
    connect(ui->actionAssetAndNetWorthTracking, &QAction::triggered, this, &MainWindow::onActionAssetAndNetWorthSummaryTriggered);
    connect(ui->actionMortgageInformation, &QAction::triggered, this, &MainWindow::onActionMortgageInformationTriggered);
    connect(ui->actionAddExpenseTransaction, &QAction::triggered, this, &MainWindow::onActionAddExpenseTransactionTriggered);
    connect(ui->actionAddExpenseType, &QAction::triggered, this, &MainWindow::onActionAddExpenseTypeTriggered);
    connect(ui->actionModifyExpenseType, &QAction::triggered, this, &MainWindow::onActionModifyExpenseTypeTriggered);
    connect(ui->actionAddInvestmentTransaction, &QAction::triggered, this, &MainWindow::onActionAddInvestmentTransactionTriggered);
    connect(ui->actionAddInvestmentType, &QAction::triggered, this, &MainWindow::onActionAddInvestmentTypeTriggered);
    connect(ui->actionModifyInvestmentType, &QAction::triggered, this, &MainWindow::onActionModifyInvestmentTypeTriggered);
    connect(ui->actionAddIncomeTransaction, &QAction::triggered, this, &MainWindow::onActionAddIncomeTransactionTriggered);
    connect(ui->actionModifyAutomaticMonthlyPayment, &QAction::triggered, this, &MainWindow::onActionModifyAutomaticMonthlyPaymentTriggered);
    connect(ui->actionAddNewAsset, &QAction::triggered, this, &MainWindow::onActionAddNewAssetTriggered);
    connect(ui->actionModifyAssetInfo, &QAction::triggered, this, &MainWindow::onActionModifyAssetInfoTriggered);
    connect(ui->actionModifyMortgageInformation, &QAction::triggered, this, &MainWindow::onActionModifyMortgageInfoTriggered);

    connect(mainWindowController.get(), &MainWindowController::requestMainWindowUpdate, this, &MainWindow::updateDisplayedInformation);

    updateDisplayedInformation();
}

MainWindow::~MainWindow()
{
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

void MainWindow::onActionMonthlyBudgetExpenseTypeSummaryTriggered()
{
    mainWindowController->showExpenseTypeSelectionDialog(this);
}

void MainWindow::onActionMonthlyBudgetSummaryTriggered()
{
    mainWindowController->showMonthlyBudgetSummaryDialog(this);
}

void MainWindow::onActionYearlyIncomeSummaryTriggered()
{
    mainWindowController->showYearlyIncomeSummaryDialog(this);
}

void MainWindow::onActionAutomaticMonthlyPaymentSummaryTriggered()
{
    mainWindowController->showAutomaticMonthlyPaymentSummaryDialog(this);
}

void MainWindow::onActionAssetAndNetWorthSummaryTriggered()
{
    mainWindowController->showAssetSummaryDialog(this);
}

void MainWindow::onActionMortgageInformationTriggered()
{
    mainWindowController->showMortgageSummaryDialog(this);
}

void MainWindow::onActionAddExpenseTransactionTriggered()
{
    mainWindowController->showAddExpenseTransactionDialog(this);
}

void MainWindow::onActionAddExpenseTypeTriggered()
{
    mainWindowController->showAddExpenseTypeDialog(this);
}

void MainWindow::onActionModifyExpenseTypeTriggered()
{
    mainWindowController->showModifyExpenseTypeDialog(this);
}

void MainWindow::onActionAddInvestmentTransactionTriggered()
{
    mainWindowController->showAddInvestmentTransactionDialog(this);
}

void MainWindow::onActionAddInvestmentTypeTriggered()
{
    mainWindowController->showAddInvestmentTypeDialog(this);
}

void MainWindow::onActionModifyInvestmentTypeTriggered()
{
    mainWindowController->showModifyInvestmentTypeDialog(this);
}

void MainWindow::onActionAddIncomeTransactionTriggered()
{
    mainWindowController->showAddIncomeTransactionDialog(this);
}

void MainWindow::onActionModifyAutomaticMonthlyPaymentTriggered()
{
    mainWindowController->showUpdateAutomaticMonthlyPaymentDialog(this);
}

void MainWindow::onActionAddNewAssetTriggered()
{
    mainWindowController->showAddAssetDialog(this);
}

void MainWindow::onActionModifyAssetInfoTriggered()
{
    mainWindowController->showUpdateAssetInfoDialog(this);
}

void MainWindow::onActionModifyMortgageInfoTriggered()
{
    mainWindowController->showUpdateMortgageInfoDialog(this);
}

void MainWindow::closeEvent(QCloseEvent* event)
{
    sds->saveSystemConfig();
    event->accept();
}

void MainWindow::updateDisplayedInformation()
{
    bool mortgageExists = mainWindowController->mortgageExists();
    ui->labelAdditionalPrincipalMonthly->setVisible(mortgageExists);
    ui->labelMonthlyPrincipal->setVisible(mortgageExists);
    ui->labelAdditionalPrincipalYearly->setVisible(mortgageExists);
    ui->labelYearlyPrincipal->setVisible(mortgageExists);

    if(mortgageExists)
    {
        ui->formMonthlySummary->insertRow(2, ui->labelAdditionalPrincipalMonthly, ui->labelMonthlyPrincipal);
        ui->formYearlySummary->insertRow(2, ui->labelAdditionalPrincipalYearly, ui->labelYearlyPrincipal);
    }
    else
    {
        ui->formMonthlySummary->removeWidget(ui->labelAdditionalPrincipalMonthly);
        ui->formMonthlySummary->removeWidget(ui->labelMonthlyPrincipal);
        ui->formYearlySummary->removeWidget(ui->labelAdditionalPrincipalYearly);
        ui->formYearlySummary->removeWidget(ui->labelYearlyPrincipal);
    }

    ui->groupBoxExpenseBudget->setVisible(mainWindowController->expenseTypesExist());
    ui->groupBoxInvestmentBudget->setVisible(mainWindowController->investmentTypesExist());
    ui->groupBoxIncomeDistribution->setVisible((mainWindowController->getYearlyInvestmentTotal() > 0.0) ||
                                               (mainWindowController->getYearlyExpenseTotal() > 0.0) ||
                                               (mainWindowController->getYearlyAdditionalPrincipal() > 0.0));

    expenseTableModel.setExpenseTypes();
    investmentTableModel.setInvestmentTypes();

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
    ui->labelMonthlyPrincipal->setText(QString::fromStdString(CurrencyUtilities::formatCurrency(mainWindowController->getMonthlyAdditionalPrincipal())));
    ui->labelYearlyExpenses->setText(QString::fromStdString(CurrencyUtilities::formatCurrency(mainWindowController->getYearlyExpenseTotal())));
    ui->labelYearlyInvestments->setText(QString::fromStdString(CurrencyUtilities::formatCurrency(mainWindowController->getYearlyInvestmentTotal())));
    ui->labelYearlyIncome->setText(QString::fromStdString(CurrencyUtilities::formatCurrency(mainWindowController->getYearlyIncomeTotal())));
    ui->labelYearlyCashSaved->setText(QString::fromStdString(CurrencyUtilities::formatCurrency(mainWindowController->getYearlyCashSavedTotal())));
    ui->labelYearlySavingsRatio->setText(QString::fromStdString(CurrencyUtilities::formatRatio(mainWindowController->getYearlySavingsRatio())));
    ui->labelYearlyPrincipal->setText(QString::fromStdString(CurrencyUtilities::formatCurrency(mainWindowController->getYearlyAdditionalPrincipal())));

    if(mainWindowController->isCurrentMonthOverBudget())
    {
        ui->labelBudgetStatus->setStyleSheet("font-weight: bold; color: red");
    }
}

void MainWindow::configureBudgetStatusBarChart()
{
    double expenseTotal = mainWindowController->getMonthlyExpenseTotal();
    double remainingAmount = mainWindowController->getMonthlyRemainingBudget();
    QBarSet* expenses = new QBarSet("Expenses");
    QBarSet* remainingBudget = new QBarSet("Remaining Budget");
    *expenses << expenseTotal;
    *remainingBudget << remainingAmount;
    expenses->setColor(QColorConstants::Red);
    remainingBudget->setColor(QColorConstants::DarkGreen);

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

    if((expenseTotal == 0.0) &&
       (remainingAmount == 0.0))
    {
        ui->graphicsViewExpenseBarChart->setVisible(false);
    }
}

void MainWindow::configureBreakdownPieChart()
{
    QPieSeries* series = new QPieSeries();

    QPieSlice* expenseSlice = new QPieSlice("Expenses, " + QString::fromStdString(mainWindowController->getRatioForPieChart(mainWindowController->getYearlyExpenseTotal())),
                                            mainWindowController->getYearlyExpenseTotal());
    expenseSlice->setBrush(Qt::red);
    series->append(expenseSlice);

    double cashSaved = mainWindowController->getYearlyCashSavedTotal();
    (cashSaved < 0.0) ? cashSaved = 0.0 : mainWindowController->getYearlyCashSavedTotal();
    QPieSlice* cashSlice = new QPieSlice("Cash, " + QString::fromStdString(mainWindowController->getRatioForPieChart(cashSaved)),
                                                                           cashSaved);
    cashSlice->setBrush(Qt::darkGreen);
    series->append(cashSlice);

    if(mainWindowController->mortgageExists())
    {
        QPieSlice* mortgagePrincipalSlice = new QPieSlice("Principal, " + QString::fromStdString(mainWindowController->getRatioForPieChart(mainWindowController->getYearlyAdditionalPrincipal())),
                                                          mainWindowController->getYearlyAdditionalPrincipal());
        mortgagePrincipalSlice->setBrush(Qt::yellow);
        series->append(mortgagePrincipalSlice);
    }

    for(const auto& i : mainWindowController->getInvestmentTypesAndYearlyTotals())
    {
        series->append(QString::fromStdString(i.first) + ", " + QString::fromStdString(mainWindowController->getRatioForPieChart(i.second)),
                       i.second);
    }

    series->setHoleSize(0.35);

    QChart* pieChart = new QChart();
    pieChart->addSeries(series);
    pieChart->legend()->show();
    pieChart->legend()->setAlignment(Qt::AlignRight);
    pieChart->setBackgroundVisible(false);
    pieChart->setMargins(QMargins(0,0,0,0));
    pieChart->setAnimationOptions(QChart::SeriesAnimations);

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
    ui->tableViewMonthlyExpenses->setStyleSheet("QHeaderView::section { background-color: rgb(240, 240, 240) }");

    // Disable horizontal scroll bar
    ui->tableViewMonthlyExpenses->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    // Disable cell resizing and selections
    ui->tableViewMonthlyExpenses->horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed);
    ui->tableViewMonthlyExpenses->horizontalHeader()->setFixedHeight(25);
    ui->tableViewMonthlyExpenses->verticalHeader()->setSectionResizeMode(QHeaderView::Fixed);
    ui->tableViewMonthlyExpenses->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableViewMonthlyExpenses->setFocusPolicy(Qt::NoFocus);
    ui->tableViewMonthlyExpenses->setSelectionMode(QAbstractItemView::NoSelection);

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

    ui->groupBoxExpenseBudget->setMaximumHeight(ui->tableViewMonthlyExpenses->maximumHeight() + 50);

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
    ui->tableViewMonthlyInvestments->setStyleSheet("QHeaderView::section { background-color: rgb(240, 240, 240) }");

    // Disable horizontal scroll bar
    ui->tableViewMonthlyInvestments->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    // Disable cell resizing and selections
    ui->tableViewMonthlyInvestments->horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed);
    ui->tableViewMonthlyInvestments->horizontalHeader()->setFixedHeight(25);
    ui->tableViewMonthlyInvestments->verticalHeader()->setSectionResizeMode(QHeaderView::Fixed);
    ui->tableViewMonthlyInvestments->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableViewMonthlyInvestments->setFocusPolicy(Qt::NoFocus);
    ui->tableViewMonthlyInvestments->setSelectionMode(QAbstractItemView::NoSelection);

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

    ui->groupBoxInvestmentBudget->setMaximumHeight(ui->tableViewMonthlyInvestments->maximumHeight() + 50);

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
