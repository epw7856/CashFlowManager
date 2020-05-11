#ifndef MONTHLYBUDGETSUMMARYDIALOG_H
#define MONTHLYBUDGETSUMMARYDIALOG_H

#include <QDialog>

namespace Ui {
class MonthlyBudgetSummaryDialog;
}

class MonthlyBudgetSummaryDialog : public QDialog
{
    Q_OBJECT

public:
    explicit MonthlyBudgetSummaryDialog(QWidget *parent = nullptr);
    ~MonthlyBudgetSummaryDialog();

private:
    Ui::MonthlyBudgetSummaryDialog *ui;
};

#endif // MONTHLYBUDGETSUMMARYDIALOG_H
