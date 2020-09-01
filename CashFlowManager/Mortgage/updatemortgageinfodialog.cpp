#include <QMessageBox>
#include "updatemortgageinfodialog.h"
#include "updatemortgageinfodialogcontroller.h"
#include "ui_updatemortgageinfodialog.h"

UpdateMortgageInfoDialog::UpdateMortgageInfoDialog(MortgageInterface& localMortgageInterface, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::UpdateMortgageInfoDialog),
    controller(std::make_unique<UpdateMortgageInfoDialogController>(localMortgageInterface))
{
    ui->setupUi(this);
    setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);
    setWindowFlag(Qt::WindowMinMaxButtonsHint);

    connect(ui->pushButtonExit, &QPushButton::clicked, this, &UpdateMortgageInfoDialog::onPushButtonExitClicked);
    connect(ui->pushButtonUpdate, &QPushButton::clicked, this, &UpdateMortgageInfoDialog::onPushButtonUpdateClicked);

    populateFields();
    ui->labelMonthlyPayment->setFocus();
}

UpdateMortgageInfoDialog::~UpdateMortgageInfoDialog()
{
    delete ui;
}

void UpdateMortgageInfoDialog::onPushButtonExitClicked()
{
    close();
}

void UpdateMortgageInfoDialog::onPushButtonUpdateClicked()
{
    if(!controller->verifyDollarAmount(ui->lineEditLoanAmount->text()))
    {
        QMessageBox::critical(this, tr("Error"), tr("<p align='center'>Invalid total loan amount entered.</p>"), QMessageBox::Ok);
        return;
    }
    else if(!controller->verifyDollarAmount(ui->lineEditMarketValue->text()))
    {
        QMessageBox::critical(this, tr("Error"), tr("<p align='center'>Invalid market value entered.</p>"), QMessageBox::Ok);
        return;
    }
    else if(!controller->verifyInterestRate(ui->lineEditInterestRate->text()))
    {
        QMessageBox::critical(this, tr("Error"), tr("<p align='center'>Invalid interest rate entered.</p>"), QMessageBox::Ok);
        return;
    }
    else if(!controller->verifyLoanTerm(ui->lineEditLoanTerm->text()))
    {
        QMessageBox::critical(this, tr("Error"), tr("<p align='center'>Invalid loan term entered.</p>"), QMessageBox::Ok);
        return;
    }
    else if(!controller->verifyMortgageStartDate(ui->dateEditStartDate->date()))
    {
        QMessageBox::critical(this, tr("Error"), tr("<p align='center'>Invalid mortgage starting date entered.</p>"), QMessageBox::Ok);
        return;
    }
    else
    {
        controller->updateMortgageInfo(ui->lineEditLoanAmount->text().remove(",").toDouble(),
                                       ui->lineEditMarketValue->text().remove(",").toDouble(),
                                       ui->lineEditInterestRate->text().remove("%").toDouble(),
                                       ui->lineEditLoanTerm->text().toInt(),
                                       ui->dateEditStartDate->date());

        QMessageBox::information(this, tr("Success"), tr("<p align='center'>Successfully updated mortgage information.</p>"), QMessageBox::Ok);
        populateFields();
    }
}

void UpdateMortgageInfoDialog::closeEvent(QCloseEvent*)
{
    emit dialogClosed();
}

void UpdateMortgageInfoDialog::populateFields()
{
    ui->lineEditLoanAmount->clear();
    ui->lineEditMarketValue->clear();
    ui->lineEditInterestRate->clear();
    ui->labelMonthlyPayment->clear();

    ui->lineEditLoanAmount->setText(controller->getTotalLoanAmount());
    ui->lineEditMarketValue->setText(controller->getMarketValue());
    ui->lineEditInterestRate->setText(controller->getInterestRate());
    ui->dateEditStartDate->setDate(controller->getMortgageStartDate());
    ui->labelMonthlyPayment->setText(controller->getMonthlyPayment());
}
