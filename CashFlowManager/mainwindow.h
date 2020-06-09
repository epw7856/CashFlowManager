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
    void onActionExitTriggered();
    void onActionYearlyBudgetSummaryTriggered();
    void onActionMonthlyBudgetSummaryTriggered();
    void onActionFoodExpensesTriggered();
    void onActionMiscExpensesTriggered();
    void onActionYearlyIncomeSummaryTriggered();
    void onActionAutomaticMonthlyPaymentSummaryTriggered();
    void onActionAssetAndNetWorthSummaryTriggered();
    void onActionMortgageInformationTriggered();

private:
    Ui::MainWindow *ui;
    std::unique_ptr<SystemDataSource> sds;
    std::unique_ptr<MainWindowController> mainWindowController;
    MonthlyExpenseTableModel expenseTableModel;
    MonthlyInvestmentTableModel investmentTableModel;

    void updateDisplayedInformation();
    void configureBudgetStatusBarChart();
    void configureBreakdownPieChart();
    void configureExpenseTableView();
    void configureInvestmentTableView();
};

#endif // MAINWINDOW_H
