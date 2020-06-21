#include "addexpensetransactiondialog.h"
#include "addexpensetransactiondialogcontroller.h"
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


    ui->comboBoxExpenseType->addItems(controller->getExpenseTypes());
    if(ui->comboBoxExpenseType->count() == 0)
    {
        ui->comboBoxExpenseType->insertItem(0, "No Expenses Types Found");
        disableActions();
    }
    else
    {
        ui->comboBoxExpenseType->insertItem(0, "<Expense Types>");
    }

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
        QMessageBox::critical(this, tr("Error"), tr("<p align='center'>Please select an expense type for the transaction.</p>"), QMessageBox::Ok);
    }
    else if(!controller->verifyTransactionDescription(ui->lineEditDescription->text()))
    {
        QMessageBox::critical(this, tr("Error"), tr("<p align='center'>Invalid expense transaction description entered.<br>Please enter a valid description.</p>"), QMessageBox::Ok);
    }
    else if(!controller->verifyTransactionDate(ui->dateEditTransaction->date()))
    {
        QMessageBox::critical(this, tr("Error"), tr("<p align='center'>Invalid transaction date selected.<br>Please enter a valid date within +/- 1 year of today's date.</p>"), QMessageBox::Ok);
    }
    else if(((ui->comboBoxExpenseType->currentText() == "Mortgage") &&
            (!controller->verifyTransactionAmount((ui->lineEditTransactionAmount->text()), true))) ||
            ((ui->comboBoxExpenseType->currentText() != "Mortgage") &&
            (!controller->verifyTransactionAmount((ui->lineEditTransactionAmount->text()), false))))
    {
        QMessageBox::critical(this, tr("Error"), tr("<p align='center'>Invalid transaction amount entered.<br>Please enter a valid non-zero amount.</p>"), QMessageBox::Ok);
    }
    else if((ui->comboBoxExpenseType->currentText() == "Mortgage") &&
            (!controller->verifyTransactionAmount((ui->lineEditAdditionalPrincipalAmount->text()), true)))
    {
        QMessageBox::critical(this, tr("Error"), tr("<p align='center'>Invalid additional principal amount entered.<br>Please enter a valid amount.</p>"), QMessageBox::Ok);
    }
    else
    {
        controller->addExpenseTransaction(ui->dateEditTransaction->date(),
                                          ui->comboBoxExpenseType->currentText(),
                                          ui->lineEditDescription->text(),
                                          ui->lineEditTransactionAmount->text().toDouble(),
                                          ui->lineEditAdditionalPrincipalAmount->text().toDouble());

        QMessageBox::information(this, tr("Success"), tr("<p align='center'>Successfully added expense transaction.</p>"), QMessageBox::Ok);
    }
}

void AddExpenseTransactionDialog::expenseTypeSelectionChanged(QString type)
{
    (type == "Mortgage") ? showAdditionalPrincipal() : hideAdditionalPrincipal();
}

void AddExpenseTransactionDialog::closeEvent(QCloseEvent*)
{
    emit dialogClosed();
    accept();
}

void AddExpenseTransactionDialog::hideAdditionalPrincipal()
{
    ui->lineEditDescription->clear();
    ui->labelAdditionalPrincipal->setVisible(false);
    ui->lineEditAdditionalPrincipalAmount->setVisible(false);
    ui->gridLayout->removeItem(ui->horizontalSpacer_7);
    ui->gridLayout->removeItem(ui->horizontalSpacer_8);
    ui->gridLayout->removeItem(ui->labelAdditionalPrincipal->layout());
    ui->gridLayout->removeItem(ui->lineEditAdditionalPrincipalAmount->layout());
}

void AddExpenseTransactionDialog::showAdditionalPrincipal()
{
    ui->lineEditDescription->clear();
    ui->lineEditDescription->setText(QDate::currentDate().toString("MMMM") + " Mortgage Payment");
    ui->labelAdditionalPrincipal->setVisible(true);
    ui->lineEditAdditionalPrincipalAmount->setVisible(true);
    ui->gridLayout->addLayout(ui->horizontalSpacer_7->layout(), ui->gridLayout->rowCount() - 1, 0);
    ui->gridLayout->addWidget(ui->labelAdditionalPrincipal, ui->gridLayout->rowCount() - 1, 1);
    ui->gridLayout->addWidget(ui->lineEditAdditionalPrincipalAmount, ui->gridLayout->rowCount() - 1, 2);
    ui->gridLayout->addLayout(ui->horizontalSpacer_8->layout(), ui->gridLayout->rowCount() - 1, 3);
}

void AddExpenseTransactionDialog::disableActions()
{
    ui->lineEditDescription->setEnabled(false);
    ui->dateEditTransaction->setEnabled(false);
    ui->lineEditTransactionAmount->setEnabled(false);
    ui->lineEditAdditionalPrincipalAmount->setEnabled(false);
    ui->pushButtonAddTransaction->setEnabled(false);
}
