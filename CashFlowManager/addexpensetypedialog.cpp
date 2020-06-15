#include "addexpensetypedialog.h"
#include "expenseinterface.h"
#include "ui_addexpensetypedialog.h"

AddExpenseTypeDialog::AddExpenseTypeDialog(ExpenseInterface& localExpenseInterface, QWidget* parent) :
    QDialog(parent),
    ui(new Ui::AddExpenseTypeDialog),
    expenseInterface(localExpenseInterface)
{
    ui->setupUi(this);
    setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);
    setWindowFlag(Qt::WindowMinMaxButtonsHint);

    connect(ui->pushButtonExit, &QPushButton::clicked, this, &AddExpenseTypeDialog::onPushButtonExitClicked);
    connect(ui->pushButtonAddType, &QPushButton::clicked, this, &AddExpenseTypeDialog::onPushButtonAddTypeClicked);
    connect(ui->radioButtonFixed, &QRadioButton::toggled, this, &AddExpenseTypeDialog::onRadioButtonToggled);
}

AddExpenseTypeDialog::~AddExpenseTypeDialog()
{
    delete ui;
}

void AddExpenseTypeDialog::onPushButtonExitClicked()
{
    close();
}

void AddExpenseTypeDialog::onPushButtonAddTypeClicked()
{
    //check if expense type already exists plus other checks
}

void AddExpenseTypeDialog::onRadioButtonToggled()
{
    (ui->radioButtonFixed->isChecked()) ? ui->lineEditBudgetAmount->setEnabled(true) : ui->lineEditBudgetAmount->setEnabled(false);
}
