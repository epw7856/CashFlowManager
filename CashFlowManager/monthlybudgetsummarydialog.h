#ifndef MONTHLYBUDGETSUMMARYDIALOG_H
#define MONTHLYBUDGETSUMMARYDIALOG_H

#include <memory>
#include "monthlyexpensetablemodel.h"
#include "monthlyinvestmenttablemodel.h"
#include <QAbstractTableModel>
#include <QDialog>

class IncomeInterface;
class MonthlyBudgetSummaryDialogController;
class MortgageInterface;
class QLabel;
class QTableView;

namespace Ui {
class MonthlyBudgetSummaryDialog;
}

class MonthlyBudgetSummaryDialog : public QDialog
{
    Q_OBJECT

public:
    explicit MonthlyBudgetSummaryDialog(ExpenseInterface& localExpenseInterface,
                                        IncomeInterface& localIncomeInterface,
                                        InvestmentInterface& localInvestmentInterface,
                                        MortgageInterface& localMortgageInterface,
                                        QWidget* parent = nullptr);
    ~MonthlyBudgetSummaryDialog();
    void showEvent(QShowEvent*event);

public slots:
    void onPushButtonExitClicked();

private:
    Ui::MonthlyBudgetSummaryDialog *ui;
    std::unique_ptr<MonthlyBudgetSummaryDialogController> controller;

    MonthlyExpenseTableModel januaryExpenseTableModel;
    MonthlyExpenseTableModel februaryExpenseTableModel;
    MonthlyExpenseTableModel marchExpenseTableModel;
    MonthlyExpenseTableModel aprilExpenseTableModel;
    MonthlyExpenseTableModel mayExpenseTableModel;
    MonthlyExpenseTableModel juneExpenseTableModel;
    MonthlyExpenseTableModel julyExpenseTableModel;
    MonthlyExpenseTableModel augustExpenseTableModel;
    MonthlyExpenseTableModel septemberExpenseTableModel;
    MonthlyExpenseTableModel octoberExpenseTableModel;
    MonthlyExpenseTableModel novemberExpenseTableModel;
    MonthlyExpenseTableModel decemberExpenseTableModel;

    MonthlyInvestmentTableModel januaryInvestmentTableModel;
    MonthlyInvestmentTableModel februaryInvestmentTableModel;
    MonthlyInvestmentTableModel marchInvestmentTableModel;
    MonthlyInvestmentTableModel aprilInvestmentTableModel;
    MonthlyInvestmentTableModel mayInvestmentTableModel;
    MonthlyInvestmentTableModel juneInvestmentTableModel;
    MonthlyInvestmentTableModel julyInvestmentTableModel;
    MonthlyInvestmentTableModel augustInvestmentTableModel;
    MonthlyInvestmentTableModel septemberInvestmentTableModel;
    MonthlyInvestmentTableModel octoberInvestmentTableModel;
    MonthlyInvestmentTableModel novemberInvestmentTableModel;
    MonthlyInvestmentTableModel decemberInvestmentTableModel;

    int maxColumnWidth = 0;
    int tableWidth = 0;
    int expenseTableHeight = 0;
    int investmentTableHeight = 0;

    void setTableData();
    void setCashSavedLabels();
    void configureTable(QTableView* tableView, QAbstractTableModel& tableModel, bool isExpenseTable);
    void setLabelColor(QLabel* label);
};

#endif // MONTHLYBUDGETSUMMARYDIALOG_H
