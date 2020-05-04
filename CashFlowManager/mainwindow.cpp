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
    loadBudgetBreakdown();
}

MainWindow::~MainWindow()
{
    sds->saveSystemConfig();
    delete ui;
}

void MainWindow::loadBudgetBreakdown()
{
    ui->labelCurrentMonth->setText(QString::fromStdString(budgetBreakdownController->getCurrentMonthAndYear()));
    ui->labelBudgetStatus->setText(QString::fromStdString(budgetBreakdownController->getBudgetStatusStatement()));
    ui->labelMonthlyExpenses->setText(QString::fromStdString(CurrencyUtilities::formatCurrency(budgetBreakdownController->getTotalMonthlyExpenses())));
}
