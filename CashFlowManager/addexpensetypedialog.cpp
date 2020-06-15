#include "addexpensetypedialog.h"
#include "addexpensetypedialogcontroller.h"
#include "expenseinterface.h"
#include <QMessageBox>
#include "ui_addexpensetypedialog.h"

AddExpenseTypeDialog::AddExpenseTypeDialog(ExpenseInterface& localExpenseInterface, QWidget* parent) :
    QDialog(parent),
    ui(new Ui::AddExpenseTypeDialog),
    expenseInterface(localExpenseInterface),
    controller(std::make_unique<AddExpenseTypeDialogController>(localExpenseInterface))
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
    if(!controller->verifyTypeName(ui->lineEditName->text()))
    {
        QMessageBox::critical(this, tr("Error"), tr("<p align='center'>Invalid expense type name entered.<br>Please enter a valid name.</p>"), QMessageBox::Ok);
    }
    else if(ui->radioButtonFixed->isChecked() && !controller->verifyBudgetAmount(ui->lineEditBudgetAmount->text(), false))
    {
        QMessageBox::critical(this, tr("Error"), tr("<p align='center'>No monthly budget amount entered for fixed expense type.<br>Please enter a valid, non-zero amount.</p>"), QMessageBox::Ok);
    }
    else if(!controller->verifyUniqueTypeName(ui->lineEditName->text()))
    {
        QMessageBox::critical(this, tr("Error"), tr("<p align='center'>Expense type already exists.<br>Please enter a valid, unique expense type name.</p>"), QMessageBox::Ok);
    }
    else
    {
        controller->addExpenseType(ui->lineEditName->text(), ui->lineEditBudgetAmount->text().toDouble());
        QMessageBox::information(this, tr("Success"), tr("<p align='center'>Successfully added expense type.</p>"), QMessageBox::Ok);
    }
}

void AddExpenseTypeDialog::onRadioButtonToggled()
{
    if(ui->radioButtonFixed->isChecked())
    {
        ui->lineEditBudgetAmount->setText(controller->getFixedExpenseBudgetAmount(ui->lineEditName->text()));
        ui->lineEditBudgetAmount->setEnabled(true);
    }
    else
    {
        ui->lineEditBudgetAmount->setText("0.00");
        ui->lineEditBudgetAmount->setEnabled(false);
    };
}
