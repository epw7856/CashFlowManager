#include "addinvestmenttransactiondialog.h"
#include "addinvestmenttransactiondialogcontroller.h"
#include <QMessageBox>
#include "ui_addinvestmenttransactiondialog.h"

AddInvestmentTransactionDialog::AddInvestmentTransactionDialog(InvestmentInterface& localInvestmentInterface, QWidget *parent)
:
    QDialog(parent),
    ui(new Ui::AddInvestmentTransactionDialog),
    controller(std::make_unique<AddInvestmentTransactionDialogController>(localInvestmentInterface))
{
    ui->setupUi(this);
    setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);
    setWindowFlag(Qt::WindowMinMaxButtonsHint);

    ui->comboBoxInvestmentType->addItems(controller->getInvestmentTypes());
    if(ui->comboBoxInvestmentType->count() == 0)
    {
        ui->comboBoxInvestmentType->insertItem(0, "No Investment Types Found");
        disableActions();
    }
    else
    {
        ui->comboBoxInvestmentType->insertItem(0, "<Investment Types>");
    }

    ui->comboBoxInvestmentType->setCurrentIndex(0);
    ui->dateEditTransaction->setDate(QDate::currentDate());

    connect(ui->pushButtonExit, &QPushButton::clicked, this, &AddInvestmentTransactionDialog::onPushButtonExitClicked);
    connect(ui->pushButtonAddTransaction, &QPushButton::clicked, this, &AddInvestmentTransactionDialog::onPushButtonAddTransaction);
}

AddInvestmentTransactionDialog::~AddInvestmentTransactionDialog()
{
    delete ui;
}

void AddInvestmentTransactionDialog::onPushButtonExitClicked()
{
    close();
}

void AddInvestmentTransactionDialog::onPushButtonAddTransaction()
{
    if(ui->comboBoxInvestmentType->currentIndex() == 0)
    {
        QMessageBox::critical(this, tr("Error"), tr("<p align='center'>Please select an investment type for the transaction.</p>"), QMessageBox::Ok);
        return;
    }
    else if(!controller->verifyTransactionDate(ui->dateEditTransaction->date()))
    {
        QMessageBox::critical(this, tr("Error"), tr("<p align='center'>Invalid transaction date selected.<br>Please enter a valid date within +/- 1 year of today's date.</p>"), QMessageBox::Ok);
        return;
    }
    else if(!controller->verifyTransactionAmount(ui->lineEditTransactionAmount->text()))
    {
        QMessageBox::critical(this, tr("Error"), tr("<p align='center'>Invalid transaction amount entered.<br>Please enter a valid non-zero amount.</p>"), QMessageBox::Ok);
        return;
    }
    else
    {
        controller->addInvestmentTransaction(ui->dateEditTransaction->date(),
                                             ui->comboBoxInvestmentType->currentText(),
                                             ui->lineEditTransactionAmount->text().remove(',').toDouble());

        QMessageBox::information(this, tr("Success"), tr("<p align='center'>Successfully added investment transaction.</p>"), QMessageBox::Ok);
    }
    resetDialog();
}

void AddInvestmentTransactionDialog::closeEvent(QCloseEvent*)
{
    emit dialogClosed();
    accept();
}

void AddInvestmentTransactionDialog::disableActions()
{
    ui->lineEditTransactionAmount->setEnabled(false);
    ui->dateEditTransaction->setEnabled(false);
    ui->pushButtonAddTransaction->setEnabled(false);
}

void AddInvestmentTransactionDialog::resetDialog()
{
    ui->comboBoxInvestmentType->setCurrentIndex(0);
    ui->dateEditTransaction->setDate(QDate::currentDate());
    ui->lineEditTransactionAmount->setText("0.00");
}
