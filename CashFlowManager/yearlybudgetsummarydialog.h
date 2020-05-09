#ifndef YEARLYBUDGETSUMMARYDIALOG_H
#define YEARLYBUDGETSUMMARYDIALOG_H

#include <QDialog>

namespace Ui {
class YearlyBudgetSummaryDialog;
}

class YearlyBudgetSummaryDialog : public QDialog
{
    Q_OBJECT

public:
    explicit YearlyBudgetSummaryDialog(QWidget *parent = nullptr);
    ~YearlyBudgetSummaryDialog();

private:
    Ui::YearlyBudgetSummaryDialog *ui;
};

#endif // YEARLYBUDGETSUMMARYDIALOG_H
