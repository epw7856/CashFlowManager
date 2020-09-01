#include "updatemortgageinfodialog.h"
#include "ui_updatemortgageinfodialog.h"

UpdateMortgageInfoDialog::UpdateMortgageInfoDialog(MortgageInterface& localMortgageInterface, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::UpdateMortgageInfoDialog)
{
    ui->setupUi(this);
}

UpdateMortgageInfoDialog::~UpdateMortgageInfoDialog()
{
    delete ui;
}
