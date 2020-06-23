#include "updateautomaticmonthlypaymentsdialog.h"
#include "ui_updateautomaticmonthlypaymentsdialog.h"

UpdateAutomaticMonthlyPaymentsDialog::UpdateAutomaticMonthlyPaymentsDialog(ExpenseInterface& localExpenseInterface, QWidget* parent) :
    QDialog(parent),
    ui(new Ui::UpdateAutomaticMonthlyPaymentsDialog),
    paymentTable(localExpenseInterface)
{
    ui->setupUi(this);
    setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);
    setWindowFlag(Qt::WindowMinMaxButtonsHint);
}

UpdateAutomaticMonthlyPaymentsDialog::~UpdateAutomaticMonthlyPaymentsDialog()
{
    delete ui;
}

void UpdateAutomaticMonthlyPaymentsDialog::onPushButtonExitClicked()
{
    close();
}

void UpdateAutomaticMonthlyPaymentsDialog::onPushButtonAddPayment()
{

}

void UpdateAutomaticMonthlyPaymentsDialog::onPushButtonUpdatePayment()
{

}

void UpdateAutomaticMonthlyPaymentsDialog::onPushButtonDeletePayment()
{

}

void UpdateAutomaticMonthlyPaymentsDialog::radioButtonToggled()
{

}

void UpdateAutomaticMonthlyPaymentsDialog::closeEvent(QCloseEvent *)
{
    emit dialogClosed();
    accept();
}

void UpdateAutomaticMonthlyPaymentsDialog::configurePaymentTable()
{

}

void UpdateAutomaticMonthlyPaymentsDialog::enableAddPayment()
{

}

void UpdateAutomaticMonthlyPaymentsDialog::enableUpdatePayment()
{

}
