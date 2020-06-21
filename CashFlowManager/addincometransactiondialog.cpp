#include "addincometransactiondialog.h"
#include "addincometransactiondialogcontroller.h"
#include "ui_addincometransactiondialog.h"

AddIncomeTransactionDialog::AddIncomeTransactionDialog(IncomeInterface& localIncomeInterface, QWidget* parent) :
    QDialog(parent),
    ui(new Ui::AddIncomeTransactionDialog),
    controller(std::make_unique<AddIncomeTransactionDialogController>(localIncomeInterface))
{
    ui->setupUi(this);
    setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);
    setWindowFlag(Qt::WindowMinMaxButtonsHint);

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

}

void AddIncomeTransactionDialog::onRadioButtonToggled()
{

}

void AddIncomeTransactionDialog::closeEvent(QCloseEvent *)
{
    emit dialogClosed();
    accept();
}
