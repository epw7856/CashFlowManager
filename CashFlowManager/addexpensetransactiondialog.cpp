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
    ui->comboBoxExpenseType->addItems(controller->getExpenseTypes());

    connect(ui->pushButtonExit, &QPushButton::clicked, this, &AddExpenseTransactionDialog::onPushButtonExitClicked);
}

AddExpenseTransactionDialog::~AddExpenseTransactionDialog()
{
    delete ui;
}

void AddExpenseTransactionDialog::onPushButtonExitClicked()
{
    close();
}
