#include "expensetypeselectdialog.h"
#include <QMessageBox>
#include "ui_expensetypeselectdialog.h"

ExpenseTypeSelectDialog::ExpenseTypeSelectDialog(const QStringList& expenseTypes, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ExpenseTypeSelectDialog)
{
    ui->setupUi(this);
    setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);
    setWindowFlag(Qt::WindowMinMaxButtonsHint);

    ui->comboBoxExpenseType->clear();
    if(expenseTypes.isEmpty())
    {
        ui->comboBoxExpenseType->insertItem(0, "No Expense Types Found");
    }
    else
    {
        ui->comboBoxExpenseType->insertItem(0, "<Expense Types>");
        ui->comboBoxExpenseType->addItems(expenseTypes);
    }

    connect(ui->pushButtonExit, &QPushButton::clicked, this, &ExpenseTypeSelectDialog::onPushButtonExitClicked);
    connect(ui->pushButtonOk, &QPushButton::clicked, this, &ExpenseTypeSelectDialog::onPushButtonOkClicked);
}

ExpenseTypeSelectDialog::~ExpenseTypeSelectDialog()
{
    delete ui;
}

void ExpenseTypeSelectDialog::onPushButtonExitClicked()
{
    close();
}

void ExpenseTypeSelectDialog::onPushButtonOkClicked()
{
    if(ui->comboBoxExpenseType->currentIndex() > 0)
    {
        emit expenseTypeSelected(ui->comboBoxExpenseType->currentText());
        close();
    }
    else
    {
        QMessageBox::warning(this, tr("Error"), tr("<p align='center'>Please select an expense type.</p>"), QMessageBox::Ok);
        return;
    }
}
