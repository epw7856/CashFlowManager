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

signals:
    void dialogClosed();

public slots:
    void onPushButtonExitClicked();
    void onPushButtonAddTypeClicked();
    void onPushButtonUpdateTypeClicked();
    void onPushButtonDeleteTypeClicked();
    void onRadioButtonMonthlyCharacteristicToggled();
    void expenseTypeSelectionChanged(QString type);
    void closeEvent(QCloseEvent*) override;

private:
    void updateComboBox();
    void disableActions();

    Ui::AddExpenseTypeDialog *ui;
    ExpenseInterface& expenseInterface;
    MortgageInterface& mortgageInterface;
    std::unique_ptr<AddExpenseTypeDialogController> controller;
    bool dialogModify = false;
};

#endif // ADDEXPENSETYPEDIALOG_H
