#ifndef MONTHLYBUDGETSUMMARYDIALOG_H
#define MONTHLYBUDGETSUMMARYDIALOG_H

#include "monthlyexpensetablemodel.h"
#include "monthlyinvestmenttablemodel.h"
#include <QAbstractTableModel>
#include <QDialog>
#include <QTableView>

namespace Ui {
class MonthlyBudgetSummaryDialog;
}

class MonthlyBudgetSummaryDialog : public QDialog
{
    Q_OBJECT

public:
    explicit MonthlyBudgetSummaryDialog(ExpenseInterface& localExpenseInterface,
                                        InvestmentInterface& localInvestmentInterface,
                                        QWidget* parent = nullptr);
    ~MonthlyBudgetSummaryDialog();

private:
    Ui::MonthlyBudgetSummaryDialog *ui;

    MonthlyExpenseTableModel januaryExpenseTableModel;
    MonthlyExpenseTableModel februaryExpenseTableModel;
    MonthlyExpenseTableModel marchExpenseTableModel;
    MonthlyExpenseTableModel aprilExpenseTableModel;
    MonthlyExpenseTableModel mayExpenseTableModel;
    MonthlyExpenseTableModel juneExpenseTableModel;
    MonthlyExpenseTableModel julyExpenseTableModel;
    MonthlyExpenseTableModel augustExpenseTableModel;

    MonthlyInvestmentTableModel januaryInvestmentTableModel;
    MonthlyInvestmentTableModel februaryInvestmentTableModel;
    MonthlyInvestmentTableModel marchInvestmentTableModel;
    MonthlyInvestmentTableModel aprilInvestmentTableModel;
    MonthlyInvestmentTableModel mayInvestmentTableModel;
    MonthlyInvestmentTableModel juneInvestmentTableModel;
    MonthlyInvestmentTableModel julyInvestmentTableModel;
    MonthlyInvestmentTableModel augustInvestmentTableModel;

    int maxColumnWidth = 0;
    int tableWidth = 0;
    int expenseTableHeight = 0;
    int investmentTableHeight = 0;

    void setTableData();
    void configureTable(QTableView* tableView, QAbstractTableModel& tableModel, bool isExpenseTable);
};

#endif // MONTHLYBUDGETSUMMARYDIALOG_H
