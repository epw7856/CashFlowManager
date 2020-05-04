#include "budgetbreakdowncontroller.h"
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
    ui->labelMonthlyExpenses->setText(QString::fromStdString(budgetBreakdownController->getMonthlyExpenses()));
    ui->labelMonthlyInvestments->setText(QString::fromStdString(budgetBreakdownController->getMonthlyInvestments()));
    ui->labelMonthlyIncome->setText(QString::fromStdString(budgetBreakdownController->getMonthlyIncome()));
    ui->labelMonthlyBudgetSurplus->setText(QString::fromStdString(budgetBreakdownController->getMonthlyBudgetSurplus()));
    ui->labelMonthlyCashSaved->setText(QString::fromStdString(budgetBreakdownController->getMonthlyCashSaved()));
    ui->labelYearlyExpenses->setText(QString::fromStdString(budgetBreakdownController->getYearlyExpenses()));
    ui->labelYearlyIncome->setText(QString::fromStdString(budgetBreakdownController->getYearlyIncome()));
    ui->labelYearlySavings->setText(QString::fromStdString(budgetBreakdownController->getYearlyAmountSaved()));
    ui->labelYearlySavingsRatio->setText(QString::fromStdString(budgetBreakdownController->getYearlySavingsRatio()));

}
