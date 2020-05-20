#include "automaticmonthlypaymentsummarydialog.h"
#include "ui_automaticmonthlypaymentsummarydialog.h"

AutomaticMonthlyPaymentSummaryDialog::AutomaticMonthlyPaymentSummaryDialog
(
    ExpenseInterface& localExpenseInterface,
    QWidget *parent
)
:
    QDialog(parent),
    ui(new Ui::AutomaticMonthlyPaymentSummaryDialog),
    autoPaymentTableModel(localExpenseInterface)
{
    ui->setupUi(this);
}

AutomaticMonthlyPaymentSummaryDialog::~AutomaticMonthlyPaymentSummaryDialog()
{
    delete ui;
}
