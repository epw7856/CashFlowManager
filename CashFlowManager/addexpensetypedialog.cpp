#include "addexpensetypedialog.h"
#include "addexpensetypedialogcontroller.h"
#include "expenseinterface.h"
#include "mortgageinterface.h"
#include <QMessageBox>
#include "ui_addexpensetypedialog.h"

AddExpenseTypeDialog::AddExpenseTypeDialog(ExpenseInterface& localExpenseInterface, MortgageInterface& localMortgageInterface, bool modifyFlag, QWidget* parent) :
    QDialog(parent),
    ui(new Ui::AddExpenseTypeDialog),
    expenseInterface(localExpenseInterface),
    mortgageInterface(localMortgageInterface),
    controller(std::make_unique<AddExpenseTypeDialogController>(localExpenseInterface, localMortgageInterface)),
    dialogModify(modifyFlag)
{
    ui->setupUi(this);
    setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);
    setWindowFlag(Qt::WindowMinMaxButtonsHint);

    if(modifyFlag)
    {
        setWindowTitle("Update/Delete Expense Type");
        ui->pushButtonAddType->setVisible(false);
        updateComboBox();

        connect(ui->comboBoxExpenseType, SIGNAL(currentTextChanged(QString)), this, SLOT(expenseTypeSelectionChanged(QString)));
        connect(ui->pushButtonUpdateType, &QPushButton::clicked, this, &AddExpenseTypeDialog::onPushButtonUpdateTypeClicked);
        connect(ui->pushButtonDeleteType, &QPushButton::clicked, this, &AddExpenseTypeDialog::onPushButtonDeleteTypeClicked);
    }
    else
    {
        setWindowTitle("Add Expense Type");
        ui->pushButtonUpdateType->setVisible(false);
        ui->pushButtonDeleteType->setVisible(false);
        ui->label->setVisible(false);
        ui->comboBoxExpenseType->setVisible(false);
        ui->horizontalLayout_2->removeItem(ui->horizontalSpacer_3);
        ui->horizontalLayout_2->removeItem(ui->horizontalSpacer_4);

        connect(ui->pushButtonAddType, &QPushButton::clicked, this, &AddExpenseTypeDialog::onPushButtonAddTypeClicked);
    }

    connect(ui->pushButtonExit, &QPushButton::clicked, this, &AddExpenseTypeDialog::onPushButtonExitClicked);
    connect(ui->radioButtonFixed, &QRadioButton::toggled, this, &AddExpenseTypeDialog::onRadioButtonToggled);
}

AddExpenseTypeDialog::~AddExpenseTypeDialog()
{
    delete ui;
}

void AddExpenseTypeDialog::closeEvent(QCloseEvent*)
{
    emit dialogClosed();
    close();
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
        QMessageBox::critical(this, tr("Error"), tr("<p align='center'>Invalid monthly budget amount entered for fixed expense type.<br>Please enter a valid, non-zero amount.</p>"), QMessageBox::Ok);
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

void AddExpenseTypeDialog::onPushButtonUpdateTypeClicked()
{
    if(ui->comboBoxExpenseType->currentIndex() > 0)
    {
        if(!controller->verifyTypeName(ui->lineEditName->text()))
        {
            QMessageBox::critical(this, tr("Error"), tr("<p align='center'>Invalid expense type name entered.<br>Please enter a valid name.</p>"), QMessageBox::Ok);
            return;
        }
        else if(ui->radioButtonFixed->isChecked() && !controller->verifyBudgetAmount(ui->lineEditBudgetAmount->text(), false))
        {
            QMessageBox::critical(this, tr("Error"), tr("<p align='center'>Invalid monthly budget amount entered for fixed expense type.<br>Please enter a valid, non-zero amount.</p>"), QMessageBox::Ok);
            return;
        }
        else
        {
            controller->updateExpenseType(ui->comboBoxExpenseType->currentText(), ui->lineEditName->text(), ui->lineEditBudgetAmount->text().toDouble());
            QMessageBox::information(this, tr("Success"), tr("<p align='center'>Successfully updated expense type.</p>"), QMessageBox::Ok);
        }
    }
    else
    {
        QMessageBox::critical(this, tr("Error"), "<p align='center'>No expense type has been selected.<br>Please select an expense type to be updated.</p>", QMessageBox::Ok);
        return;
    }

    updateComboBox();
}

void AddExpenseTypeDialog::onPushButtonDeleteTypeClicked()
{
    if(ui->comboBoxExpenseType->currentIndex() > 0)
    {
        if(controller->expenseTypeContainsYearlyTransactions(ui->comboBoxExpenseType->currentText()))
        {
            QMessageBox::critical(this, tr("Error"), "<p align='center'>The expense type '" + ui->comboBoxExpenseType->currentText() + "' contains transactions for the current year.<br>Cannot delete selected expense type.</p>", QMessageBox::Ok);
            return;
        }
        else
        {
            int returnValue = QMessageBox::warning(this, tr("Confirm Selection"), "Are you sure you want to delete expense type '" + ui->comboBoxExpenseType->currentText() + "'?", QMessageBox::Yes | QMessageBox::No);

            switch (returnValue)
            {
              case QMessageBox::Yes:

                  expenseInterface.deleteExpenseType(ui->comboBoxExpenseType->currentText().toStdString());
                  QMessageBox::information(this, tr("Success"), "<p align='center'>Successfully deleted expense type '" + ui->comboBoxExpenseType->currentText() + "'.</p>", QMessageBox::Ok);

                break;

              case QMessageBox::No:
                  return;

              default:
                  return;
            }
        }
    }
    else
    {
        QMessageBox::critical(this, tr("Error"), "<p align='center'>No expense type has been selected.<br>Please select an expense type to be deleted.</p>", QMessageBox::Ok);
        return;
    }

    ui->comboBoxExpenseType->setCurrentIndex(0);
    updateComboBox();
}

void AddExpenseTypeDialog::onRadioButtonToggled()
{
    if(ui->radioButtonFixed->isChecked())
    {
        ui->lineEditBudgetAmount->setText(controller->getMonthlyBudgetAmount(ui->lineEditName->text()));
        ui->lineEditBudgetAmount->setEnabled(true);
    }
    else
    {
        ui->lineEditBudgetAmount->setText("0.00");
        ui->lineEditBudgetAmount->setEnabled(false);
    }
}

void AddExpenseTypeDialog::expenseTypeSelectionChanged(QString type)
{
    if(ui->comboBoxExpenseType->currentIndex() > 0)
    {
        ui->lineEditName->setText(type);
        ui->lineEditBudgetAmount->setText(controller->getMonthlyBudgetAmount(type));
        if(controller->getMonthlyBudgetAmount(type) != "0.00")
        {
            ui->radioButtonFixed->setChecked(true);
            ui->lineEditBudgetAmount->setEnabled(true);
        }
        else
        {
            ui->radioButtonVariable->setChecked(true);
            ui->lineEditBudgetAmount->setText("0.00");
            ui->lineEditBudgetAmount->setEnabled(false);
        }
    }
    else
    {
        ui->radioButtonFixed->setChecked(true);
        ui->lineEditName->clear();
        ui->lineEditBudgetAmount->setText("0.00");
    }
}

void AddExpenseTypeDialog::updateComboBox()
{
    ui->comboBoxExpenseType->clear();
    ui->comboBoxExpenseType->insertItem(0, "<Expense Types>");
    ui->comboBoxExpenseType->addItems(controller->getExpenseTypes());
}
