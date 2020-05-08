#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "expensetablemodel.h"
#include "investmenttablemodel.h"
#include <memory>
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

private:
    Ui::MainWindow *ui;
    std::unique_ptr<SystemDataSource> sds;
    std::unique_ptr<MainWindowController> mainWindowController;
    ExpenseTableModel expenseTableModel;
    InvestmentTableModel investmentTableModel;

    void loadBudgetBreakdown();
    void configureBudgetStatusBarChart();
    void configureBreakdownPieChart();
    void configureExpenseTableView();
    void configureInvestmentTableView();
};

#endif // MAINWINDOW_H
