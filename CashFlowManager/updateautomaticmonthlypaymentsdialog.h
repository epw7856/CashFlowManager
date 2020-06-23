#ifndef UPDATEAUTOMATICMONTHLYPAYMENTSDIALOG_H
#define UPDATEAUTOMATICMONTHLYPAYMENTSDIALOG_H

#include "automaticmonthlypaymenttablemodel.h"
#include <QDialog>

class ExpenseInterface;

namespace Ui {
class UpdateAutomaticMonthlyPaymentsDialog;
}

class UpdateAutomaticMonthlyPaymentsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit UpdateAutomaticMonthlyPaymentsDialog(ExpenseInterface& localExpenseInterface, QWidget *parent = nullptr);
    ~UpdateAutomaticMonthlyPaymentsDialog();

signals:
    void dialogClosed();

public slots:
    void onPushButtonExitClicked();
    void onPushButtonAddPayment();
    void onPushButtonUpdatePayment();
    void onPushButtonDeletePayment();
    void radioButtonToggled();
    void closeEvent(QCloseEvent*) override;

private:
    Ui::UpdateAutomaticMonthlyPaymentsDialog *ui;
    AutomaticMonthlyPaymentTableModel paymentTable;

    void configurePaymentTable();
    void enableAddPayment();
    void enableUpdatePayment();
};

#endif // UPDATEAUTOMATICMONTHLYPAYMENTSDIALOG_H
