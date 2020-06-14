#include "addexpensetransactiondialog.h"
#include "addexpensetransactiondialogcontroller.h"
#include "expenseinterface.h"
#include "mortgageinterface.h"
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

}

void AddExpenseTransactionDialog::expenseTypeSelectionChanged(QString type)
{
    (type == "Mortgage") ? showAdditionalPrincipal() : hideAdditionalPrincipal();
}

void AddExpenseTransactionDialog::hideAdditionalPrincipal()
{
    ui->label_5->setVisible(false);
    ui->lineEditAdditionalPrincipalAmount->setVisible(false);
    ui->gridLayout->removeItem(ui->horizontalSpacer_7);
    ui->gridLayout->removeItem(ui->horizontalSpacer_8);
    ui->gridLayout->removeItem(ui->label_5->layout());
    ui->gridLayout->removeItem(ui->lineEditAdditionalPrincipalAmount->layout());
}

void AddExpenseTransactionDialog::showAdditionalPrincipal()
{
    ui->label_5->setVisible(true);
    ui->lineEditAdditionalPrincipalAmount->setVisible(true);
    ui->gridLayout->addLayout(ui->horizontalSpacer_7->layout(), ui->gridLayout->rowCount() - 1, 0);
    ui->gridLayout->addWidget(ui->label_5, ui->gridLayout->rowCount() - 1, 1);
    ui->gridLayout->addWidget(ui->lineEditAdditionalPrincipalAmount, ui->gridLayout->rowCount() - 1, 2);
    ui->gridLayout->addLayout(ui->horizontalSpacer_8->layout(), ui->gridLayout->rowCount() - 1, 3);
}
