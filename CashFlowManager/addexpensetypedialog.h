#ifndef ADDEXPENSETYPEDIALOG_H
#define ADDEXPENSETYPEDIALOG_H

#include <memory>
#include <QDialog>

class AddExpenseTypeDialogController;
class ExpenseInterface;
class MortgageInterface;

namespace Ui {
class AddExpenseTypeDialog;
}

class AddExpenseTypeDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddExpenseTypeDialog(ExpenseInterface& localExpenseInterface, MortgageInterface& localMortgageInterface, bool modifyFlag, QWidget* parent = nullptr);
    ~AddExpenseTypeDialog();

public slots:
    void onPushButtonExitClicked();
    void onPushButtonAddTypeClicked();
    void onPushButtonUpdateTypeClicked();
    void onPushButtonDeleteTypeClicked();
    void onRadioButtonToggled();
    void expenseTypeSelectionChanged(QString type);

private:
    void updateComboBox();

    Ui::AddExpenseTypeDialog *ui;
    ExpenseInterface& expenseInterface;
    MortgageInterface& mortgageInterface;
    std::unique_ptr<AddExpenseTypeDialogController> controller;
    bool dialogModify = false;
};

#endif // ADDEXPENSETYPEDIALOG_H
