#ifndef EXPENSETYPESUMMARYDIALOG_H
#define EXPENSETYPESUMMARYDIALOG_H

#include <QDialog>

class ExpenseInterface;

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

private:
    Ui::ExpenseTypeSummaryDialog *ui;
    ExpenseInterface& expenseInterface;
    std::string expenseType = "";
};

#endif // EXPENSETYPESUMMARYDIALOG_H
