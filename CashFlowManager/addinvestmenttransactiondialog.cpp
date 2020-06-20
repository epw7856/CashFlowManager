#include "addinvestmenttransactiondialog.h"
#include "ui_addinvestmenttransactiondialog.h"

AddInvestmentTransactionDialog::AddInvestmentTransactionDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddInvestmentTransactionDialog)
{
    ui->setupUi(this);
}

AddInvestmentTransactionDialog::~AddInvestmentTransactionDialog()
{
    delete ui;
}
