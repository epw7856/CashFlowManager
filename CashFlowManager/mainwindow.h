#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <memory>
#include "monthlyexpensetablemodel.h"
#include "monthlyinvestmenttablemodel.h"
#include <QMainWindow>

class MainWindowController;
class SystemDataSource;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void updateDisplayedInformation();
    void onActionExitTriggered();
    void onActionYearlyBudgetSummaryTriggered();
    void onActionMonthlyBudgetSummaryTriggered();
    void onActionFoodExpensesTriggered();
    void onActionMiscExpensesTriggered();
    void onActionYearlyIncomeSummaryTriggered();
    void onActionAutomaticMonthlyPaymentSummaryTriggered();
    void onActionAssetAndNetWorthSummaryTriggered();
    void onActionMortgageInformationTriggered();
    void onActionAddExpenseTransactionTriggered();
    void onActionAddExpenseTypeTriggered();
    void onActionModifyExpenseTypeTriggered();
    void onActionAddInvestmentTransactionTriggered();
    void onActionAddInvestmentTypeTriggered();
    void onActionModifyInvestmentTypeTriggered();
    void onActionAddIncomeTransactionTriggered();
    void onActionUpdateAutomaticMonthlyPaymentTriggered();

private:
    Ui::MainWindow *ui;
    std::unique_ptr<SystemDataSource> sds;
    std::unique_ptr<MainWindowController> mainWindowController;
    MonthlyExpenseTableModel expenseTableModel;
    MonthlyInvestmentTableModel investmentTableModel;

    void configureBudgetStatusBarChart();
    void configureBreakdownPieChart();
    void configureExpenseTableView();
    void configureInvestmentTableView();
};

#endif // MAINWINDOW_H
