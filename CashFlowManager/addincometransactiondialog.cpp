#include "addincometransactiondialog.h"
#include "addincometransactiondialogcontroller.h"
#include <QMessageBox>
#include "ui_addincometransactiondialog.h"

AddIncomeTransactionDialog::AddIncomeTransactionDialog(IncomeInterface& localIncomeInterface, QWidget* parent) :
    QDialog(parent),
    ui(new Ui::AddIncomeTransactionDialog),
    controller(std::make_unique<AddIncomeTransactionDialogController>(localIncomeInterface))
{
    ui->setupUi(this);
    setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);
    setWindowFlag(Qt::WindowMinMaxButtonsHint);

    enableSalaryInfo();
    ui->dateEditTransaction->setDate(QDate::currentDate());

    connect(ui->pushButtonExit, &QPushButton::clicked, this, &AddIncomeTransactionDialog::onPushButtonExitClicked);
    connect(ui->pushButtonAddTransaction, &QPushButton::clicked, this, &AddIncomeTransactionDialog::onPushButtonAddTransaction);
    connect(ui->radioButtonSalary, &QRadioButton::toggled, this, &AddIncomeTransactionDialog::onRadioButtonToggled);
}

AddIncomeTransactionDialog::~AddIncomeTransactionDialog()
{
    delete ui;
}

void AddIncomeTransactionDialog::onPushButtonExitClicked()
{
    close();
}

void AddIncomeTransactionDialog::onPushButtonAddTransaction()
{
    if(!controller->verifyTransactionAmount((ui->lineEditAmount->text())))
    {
        QMessageBox::critical(this, tr("Error"), tr("<p align='center'>Invalid income amount entered.<br>Please enter a valid non-zero amount.</p>"), QMessageBox::Ok);
        return;
    }
    else if(!controller->verifyTransactionDate(ui->dateEditTransaction->date()))
    {
        QMessageBox::critical(this, tr("Error"), tr("<p align='center'>Invalid income transaction date selected.<br>Please enter a valid date within +/- 1 year of today's date.</p>"), QMessageBox::Ok);
        return;
    }

    if(ui->radioButtonSalary->isChecked())
    {
        if(!controller->verifyOTAmount(ui->lineEditOT->text()))
        {
            QMessageBox::critical(this, tr("Error"), tr("<p align='center'>Invalid overtime amount entered.<br>Please enter a valid non-zero amount.</p>"), QMessageBox::Ok);
            return;
        }
        else
        {
            controller->addSalaryIncomeTransaction(ui->dateEditTransaction->date(),
                                                   ui->lineEditAmount->text().toDouble(),
                                                   ui->lineEditOT->text().toInt());

            QMessageBox::information(this, tr("Success"), tr("<p align='center'>Successfully added salary income transaction.</p>"), QMessageBox::Ok);
        }
    }
    else
    {
        if(!controller->verifyTransactionDescription(ui->lineEditDescription->text()))
        {
            QMessageBox::critical(this, tr("Error"), tr("<p align='center'>Invalid supplemental income transaction description entered.<br>Please enter a valid description.</p>"), QMessageBox::Ok);
            return;
        }
        else
        {
            controller->addSupplementalIncomeTransaction(ui->dateEditTransaction->date(),
                                                         ui->lineEditDescription->text(),
                                                         ui->lineEditAmount->text().toDouble());

            QMessageBox::information(this, tr("Success"), tr("<p align='center'>Successfully added supplemental income transaction.</p>"), QMessageBox::Ok);
        }
    }
}

void AddIncomeTransactionDialog::onRadioButtonToggled()
{
    (ui->radioButtonSalary->isChecked()) ? enableSalaryInfo() : enableSupplementalInfo();
}

void AddIncomeTransactionDialog::closeEvent(QCloseEvent *)
{
    emit dialogClosed();
    accept();
}

void AddIncomeTransactionDialog::enableSalaryInfo()
{
    ui->lineEditDescription->clear();
    ui->lineEditDescription->setEnabled(false);

    ui->lineEditOT->clear();
    ui->lineEditOT->setEnabled(true);
    ui->lineEditOT->setText("0");
}

void AddIncomeTransactionDialog::enableSupplementalInfo()
{
    ui->lineEditDescription->clear();
    ui->lineEditDescription->setEnabled(true);

    ui->lineEditOT->clear();
    ui->lineEditOT->setEnabled(false);
}
