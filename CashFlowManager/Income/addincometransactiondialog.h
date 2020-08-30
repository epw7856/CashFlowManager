#ifndef ADDINCOMETRANSACTIONDIALOG_H
#define ADDINCOMETRANSACTIONDIALOG_H

#include <memory>
#include <QDialog>

class AddIncomeTransactionDialogController;
class IncomeInterface;

namespace Ui {
class AddIncomeTransactionDialog;
}

class AddIncomeTransactionDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddIncomeTransactionDialog(IncomeInterface& localIncomeInterface, QWidget *parent = nullptr);
    ~AddIncomeTransactionDialog();

signals:
    void dialogClosed();

public slots:
    void onPushButtonExitClicked();
    void onPushButtonAddTransaction();
    void onRadioButtonToggled();
    void closeEvent(QCloseEvent*) override;

private:
    Ui::AddIncomeTransactionDialog *ui;
    std::unique_ptr<AddIncomeTransactionDialogController> controller;

    void enableSalaryInfo();
    void enableSupplementalInfo();
};

#endif // ADDINCOMETRANSACTIONDIALOG_H
