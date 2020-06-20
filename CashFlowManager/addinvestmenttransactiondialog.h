#ifndef ADDINVESTMENTTRANSACTIONDIALOG_H
#define ADDINVESTMENTTRANSACTIONDIALOG_H

#include <memory>
#include <QDialog>

class AddInvestmentTransactionDialogController;
class InvestmentInterface;

namespace Ui {
class AddInvestmentTransactionDialog;
}

class AddInvestmentTransactionDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddInvestmentTransactionDialog(InvestmentInterface& localInvestmentInterface, QWidget *parent = nullptr);
    ~AddInvestmentTransactionDialog();

signals:
    void dialogClosed();

public slots:
    void onPushButtonExitClicked();
    void onPushButtonAddTransaction();
    void closeEvent(QCloseEvent*) override;

private:
    void disableActions();

    Ui::AddInvestmentTransactionDialog *ui;
    std::unique_ptr<AddInvestmentTransactionDialogController> controller;
};

#endif // ADDINVESTMENTTRANSACTIONDIALOG_H
