#ifndef EXPENSETYPESUMMARYDIALOG_H
#define EXPENSETYPESUMMARYDIALOG_H

#include <QDialog>

namespace Ui {
class ExpenseTypeSummaryDialog;
}

class ExpenseTypeSummaryDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ExpenseTypeSummaryDialog(QWidget *parent = nullptr);
    ~ExpenseTypeSummaryDialog();

private:
    Ui::ExpenseTypeSummaryDialog *ui;
};

#endif // EXPENSETYPESUMMARYDIALOG_H
