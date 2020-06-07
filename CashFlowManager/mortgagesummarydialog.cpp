#include "mortgagesummarydialog.h"
#include "ui_mortgagesummarydialog.h"

MortgageSummaryDialog::MortgageSummaryDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MortgageSummaryDialog)
{
    ui->setupUi(this);
}

MortgageSummaryDialog::~MortgageSummaryDialog()
{
    delete ui;
}
