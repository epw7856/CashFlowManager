#ifndef ADDEXPENSETRANSACTIONDIALOG_H
#define ADDEXPENSETRANSACTIONDIALOG_H

#include <memory>
#include <QDialog>

class AddExpenseTransactionDialogController;
class ExpenseInterface;
class MortgageInterface;

namespace Ui {
class AddExpenseTransactionDialog;
}

class AddExpenseTransactionDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddExpenseTransactionDialog(ExpenseInterface& localExpenseInterface,
                                         MortgageInterface& localMortgageInterface,
                                         QWidget *parent = nullptr);
    ~AddExpenseTransactionDialog();

public slots:
    void onPushButtonExitClicked();

private:
    Ui::AddExpenseTransactionDialog *ui;
    std::unique_ptr<AddExpenseTransactionDialogController> controller;
};

#endif // ADDEXPENSETRANSACTIONDIALOG_H
