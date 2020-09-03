#include "expensetypeselectdialog.h"
#include <QMessageBox>
#include "ui_expensetypeselectdialog.h"

ExpenseTypeSelectDialog::ExpenseTypeSelectDialog(const QStringList& expenseTypes, QWidget* localParent) :
    QDialog(localParent),
    ui(new Ui::ExpenseTypeSelectDialog),
    parent(localParent)
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

    setFixedSize(window()->width(), window()->minimumHeight());
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
        emit expenseTypeSelected(ui->comboBoxExpenseType->currentText(), parent);
        close();
    }
    else
    {
        QMessageBox::warning(this, tr("Error"), tr("<p align='center'>Please select an expense type.</p>"), QMessageBox::Ok);
        return;
    }
}
