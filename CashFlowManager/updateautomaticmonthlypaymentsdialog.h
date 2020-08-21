#ifndef UPDATEAUTOMATICMONTHLYPAYMENTSDIALOG_H
#define UPDATEAUTOMATICMONTHLYPAYMENTSDIALOG_H

#include "automaticmonthlypaymenttablemodel.h"
#include <memory>
#include <QDialog>

class ExpenseInterface;
class UpdateAutomaticMonthlyPaymentsDialogController;

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

private slots:
        void fillFields();

public slots:
    void onPushButtonExitClicked();
    void onPushButtonAddPaymentClicked();
    void onPushButtonUpdatePaymentClicked();
    void onPushButtonDeletePaymentClicked();
    void onRadioButtonToggled();
    void closeEvent(QCloseEvent*) override;

private:
    Ui::UpdateAutomaticMonthlyPaymentsDialog *ui;
    AutomaticMonthlyPaymentTableModel paymentTable;
    std::unique_ptr<UpdateAutomaticMonthlyPaymentsDialogController> controller;

    void configurePaymentTable();
    void enableAddPayment();
    void enableUpdatePayment();
};

#endif // UPDATEAUTOMATICMONTHLYPAYMENTSDIALOG_H
