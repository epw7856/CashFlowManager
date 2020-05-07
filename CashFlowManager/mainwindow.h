#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "expensetablemodel.h"
#include <memory>
#include <QMainWindow>

class BudgetBreakdownController;
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
    std::unique_ptr<BudgetBreakdownController> budgetBreakdownController;
    ExpenseTableModel tableModel;

    void loadBudgetBreakdown();
    void configureBudgetStatusBarChart();
    void configureBreakdownPieChart();
    void configureExpenseTableView();
};

#endif // MAINWINDOW_H
