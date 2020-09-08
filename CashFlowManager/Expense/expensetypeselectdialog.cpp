#include "expensetypeselectdialog.h"
#include <QMessageBox>
#include "ui_expensetypeselectdialog.h"

ExpenseTypeSelectDialog::ExpenseTypeSelectDialog(QWidget* localParent) :
    QDialog(localParent),
    ui(new Ui::ExpenseTypeSelectDialog),
    parent(localParent)
{
    ui->setupUi(this);
    setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);
    setWindowFlag(Qt::WindowMinMaxButtonsHint);

    connect(ui->pushButtonExit, &QPushButton::clicked, this, &ExpenseTypeSelectDialog::onPushButtonExitClicked);
    connect(ui->pushButtonOk, &QPushButton::clicked, this, &ExpenseTypeSelectDialog::onPushButtonOkClicked);

    setFixedSize(window()->width(), window()->minimumHeight());
}

ExpenseTypeSelectDialog::~ExpenseTypeSelectDialog()
{
    delete ui;
}

void ExpenseTypeSelectDialog::updateExpenseTypes(const QStringList& localExpenseTypes)
{
    ui->comboBoxExpenseType->clear();
    if(localExpenseTypes.isEmpty())
    {
        ui->comboBoxExpenseType->insertItem(0, "No Expense Types Found");
        ui->pushButtonOk->setEnabled(false);
    }
    else
    {
        ui->comboBoxExpenseType->insertItem(0, "<Expense Types>");
        ui->comboBoxExpenseType->addItems(localExpenseTypes);
        ui->pushButtonOk->setEnabled(true);
    }
}

void ExpenseTypeSelectDialog::onPushButtonExitClicked()
{
    close();
}

void ExpenseTypeSelectDialog::onPushButtonOkClicked()
{
    if(ui->comboBoxExpenseType->currentIndex() > 0)
    {
        emit expenseTypeSelected(ui->comboBoxExpenseType->currentText(), parent);
        close();
    }
    else
    {
        QMessageBox::warning(this, tr("Error"), tr("<p align='center'>Please select an expense type.</p>"), QMessageBox::Ok);
        return;
    }
}
