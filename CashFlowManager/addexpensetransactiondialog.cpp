#include "addexpensetransactiondialog.h"
#include "addexpensetransactiondialogcontroller.h"
#include "expenseinterface.h"
#include "mortgageinterface.h"
#include <QMessageBox>
#include "ui_addexpensetransactiondialog.h"

AddExpenseTransactionDialog::AddExpenseTransactionDialog
(
    ExpenseInterface& localExpenseInterface,
    MortgageInterface& localMortgageInterface,
    QWidget *parent
)
:
    QDialog(parent),
    ui(new Ui::AddExpenseTransactionDialog),
    controller(std::make_unique<AddExpenseTransactionDialogController>(localExpenseInterface, localMortgageInterface))
{
    ui->setupUi(this);
    setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);
    setWindowFlag(Qt::WindowMinMaxButtonsHint);

    ui->comboBoxExpenseType->insertItem(0, "<Expense Types>");
    ui->comboBoxExpenseType->addItems(controller->getExpenseTypes());

    ui->dateEditTransaction->setDate(QDate::currentDate());

    hideAdditionalPrincipal();

    connect(ui->pushButtonExit, &QPushButton::clicked, this, &AddExpenseTransactionDialog::onPushButtonExitClicked);
    connect(ui->pushButtonAddTransaction, &QPushButton::clicked, this, &AddExpenseTransactionDialog::onPushButtonAddTransaction);
    connect(ui->comboBoxExpenseType, SIGNAL(currentTextChanged(QString)), this, SLOT(expenseTypeSelectionChanged(QString)));
}

AddExpenseTransactionDialog::~AddExpenseTransactionDialog()
{
    delete ui;
}

void AddExpenseTransactionDialog::onPushButtonExitClicked()
{
    close();
}

void AddExpenseTransactionDialog::onPushButtonAddTransaction()
{
    if(ui->comboBoxExpenseType->currentIndex() == 0)
    {
        QMessageBox::critical(this, tr("Error"), tr("Please select an expense type for the transaction."), QMessageBox::Ok);
    }
    else if(!controller->verifyDescription(ui->lineEditDescription->text()))
    {
        QMessageBox::critical(this, tr("Error"), tr("Invalid expense transaction description entered.\nPlease enter a valid description."), QMessageBox::Ok);
    }
    else if(!controller->verifyTransactionDate(ui->dateEditTransaction->date()))
    {
        QMessageBox::critical(this, tr("Error"), tr("Invalid transaction date selected.\nPlease enter a valid date within +/- 1 year of today's date."), QMessageBox::Ok);
    }
    else if(((ui->comboBoxExpenseType->currentText() == "Mortgage") &&
            (!controller->verifyAmount((ui->lineEditTransactionAmount->text()), true))) ||
            ((ui->comboBoxExpenseType->currentText() != "Mortgage") &&
            (!controller->verifyAmount((ui->lineEditTransactionAmount->text()), false))))
    {
        QMessageBox::critical(this, tr("Error"), tr("Invalid transaction amount entered.\nPlease enter a valid non-zero amount."), QMessageBox::Ok);
    }
    else if((ui->comboBoxExpenseType->currentText() == "Mortgage") &&
            (!controller->verifyAmount((ui->lineEditAdditionalPrincipalAmount->text()), true)))
    {
        QMessageBox::critical(this, tr("Error"), tr("Invalid additional principal amount entered.\nPlease enter a valid amount."), QMessageBox::Ok);
    }
    else
    {
        controller->addExpenseTransaction(ui->dateEditTransaction->date(),
                                          ui->comboBoxExpenseType->currentText(),
                                          ui->lineEditDescription->text(),
                                          ui->lineEditTransactionAmount->text().toDouble(),
                                          ui->lineEditAdditionalPrincipalAmount->text().toDouble());

        QMessageBox::information(this, tr("Success"), tr("Successfully added expense transaction."), QMessageBox::Ok);
    }
}

void AddExpenseTransactionDialog::expenseTypeSelectionChanged(QString type)
{
    (type == "Mortgage") ? showAdditionalPrincipal() : hideAdditionalPrincipal();
}

void AddExpenseTransactionDialog::hideAdditionalPrincipal()
{
    ui->lineEditDescription->clear();
    ui->label_5->setVisible(false);
    ui->lineEditAdditionalPrincipalAmount->setVisible(false);
    ui->gridLayout->removeItem(ui->horizontalSpacer_7);
    ui->gridLayout->removeItem(ui->horizontalSpacer_8);
    ui->gridLayout->removeItem(ui->label_5->layout());
    ui->gridLayout->removeItem(ui->lineEditAdditionalPrincipalAmount->layout());
}

void AddExpenseTransactionDialog::showAdditionalPrincipal()
{
    ui->lineEditDescription->clear();
    ui->lineEditDescription->setText(QDate::currentDate().toString("MMMM") + " Mortgage Payment");
    ui->label_5->setVisible(true);
    ui->lineEditAdditionalPrincipalAmount->setVisible(true);
    ui->gridLayout->addLayout(ui->horizontalSpacer_7->layout(), ui->gridLayout->rowCount() - 1, 0);
    ui->gridLayout->addWidget(ui->label_5, ui->gridLayout->rowCount() - 1, 1);
    ui->gridLayout->addWidget(ui->lineEditAdditionalPrincipalAmount, ui->gridLayout->rowCount() - 1, 2);
    ui->gridLayout->addLayout(ui->horizontalSpacer_8->layout(), ui->gridLayout->rowCount() - 1, 3);
}
