#ifndef EXPENSETYPESUMMARYDIALOG_H
#define EXPENSETYPESUMMARYDIALOG_H

#include "expensetypetablemodel.h"
#include <QDialog>

class QTableView;

namespace Ui {
class ExpenseTypeSummaryDialog;
}

class ExpenseTypeSummaryDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ExpenseTypeSummaryDialog(ExpenseInterface& localExpenseInterface,
                                      std::string localExpenseType,
                                      QWidget *parent = nullptr);
    ~ExpenseTypeSummaryDialog();

public slots:
    void onPushButtonExitClicked();

private:
    void configureExpenseTable(QTableView* tableView, QAbstractTableModel& tableModel);
    void setTableData();

    Ui::ExpenseTypeSummaryDialog *ui;
    std::string expenseType = "";

    ExpenseTypeTableModel januaryExpenseTable;
    ExpenseTypeTableModel februaryExpenseTable;
    ExpenseTypeTableModel marchExpenseTable;
    ExpenseTypeTableModel aprilExpenseTable;
    ExpenseTypeTableModel mayExpenseTable;
    ExpenseTypeTableModel juneExpenseTable;
    ExpenseTypeTableModel julyExpenseTable;
    ExpenseTypeTableModel augustExpenseTable;
    ExpenseTypeTableModel septemberExpenseTable;
    ExpenseTypeTableModel octoberExpenseTable;
    ExpenseTypeTableModel novemberExpenseTable;
    ExpenseTypeTableModel decemberExpenseTable;
};

#endif // EXPENSETYPESUMMARYDIALOG_H
