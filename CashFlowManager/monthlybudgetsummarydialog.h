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
    MonthlyInvestmentTableModel januaryInvestmentTableModel;

    void configureTable(QTableView* tableView, QAbstractTableModel& tableModel);
    void configureJanuaryTables();
};

#endif // MONTHLYBUDGETSUMMARYDIALOG_H
