#ifndef ADDEXPENSETYPEDIALOG_H
#define ADDEXPENSETYPEDIALOG_H

#include <memory>
#include <QDialog>

class AddExpenseTypeDialogController;
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
    std::unique_ptr<AddExpenseTypeDialogController> controller;
};

#endif // ADDEXPENSETYPEDIALOG_H
