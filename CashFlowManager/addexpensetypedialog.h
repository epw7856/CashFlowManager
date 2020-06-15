#ifndef ADDEXPENSETYPEDIALOG_H
#define ADDEXPENSETYPEDIALOG_H

#include <QDialog>

class ExpenseInterface;

namespace Ui {
class AddExpenseTypeDialog;
}

class AddExpenseTypeDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddExpenseTypeDialog(ExpenseInterface& localExpenseInterface, QWidget* parent = nullptr);
    ~AddExpenseTypeDialog();

public slots:
    void onPushButtonExitClicked();
    void onPushButtonAddTypeClicked();
    void onRadioButtonToggled();

private:
    Ui::AddExpenseTypeDialog *ui;
    ExpenseInterface& expenseInterface;
};

#endif // ADDEXPENSETYPEDIALOG_H
