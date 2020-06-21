#include "addinvestmenttypedialog.h"
#include "addinvestmenttypedialogcontroller.h"
#include <QMessageBox>
#include "ui_addinvestmenttypedialog.h"

AddInvestmentTypeDialog::AddInvestmentTypeDialog(InvestmentInterface& localInvestmentInterface,  bool modifyFlag, QWidget* parent) :
    QDialog(parent),
    ui(new Ui::AddInvestmentTypeDialog),
    investmentInterface(localInvestmentInterface),
    dialogModify(modifyFlag)
{
    ui->setupUi(this);
    setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);
    setWindowFlag(Qt::WindowMinMaxButtonsHint);

    if(modifyFlag)
    {
        setWindowTitle("Update/Delete Investment Type");
        ui->pushButtonAddType->setVisible(false);
        updateComboBox();

        connect(ui->comboBoxInvestmentType, SIGNAL(currentTextChanged(QString)), this, SLOT(expenseTypeSelectionChanged(QString)));
        connect(ui->pushButtonUpdateType, &QPushButton::clicked, this, &AddInvestmentTypeDialog::onPushButtonUpdateTypeClicked);
        connect(ui->pushButtonDeleteType, &QPushButton::clicked, this, &AddInvestmentTypeDialog::onPushButtonDeleteTypeClicked);
    }
    else
    {
        setWindowTitle("Add Investment Type");
        ui->pushButtonUpdateType->setVisible(false);
        ui->pushButtonDeleteType->setVisible(false);
        ui->labelInvestmentTypes->setVisible(false);
        ui->comboBoxInvestmentType->setVisible(false);
        ui->horizontalLayout_2->removeItem(ui->horizontalSpacer_3);
        ui->horizontalLayout_2->removeItem(ui->horizontalSpacer_4);

        connect(ui->pushButtonAddType, &QPushButton::clicked, this, &AddInvestmentTypeDialog::onPushButtonAddTypeClicked);
    }

    connect(ui->pushButtonExit, &QPushButton::clicked, this, &AddInvestmentTypeDialog::onPushButtonExitClicked);
}

AddInvestmentTypeDialog::~AddInvestmentTypeDialog()
{
    delete ui;
}

void AddInvestmentTypeDialog::onPushButtonExitClicked()
{
    close();
}

void AddInvestmentTypeDialog::onPushButtonAddTypeClicked()
{
    if(!controller->verifyTypeName(ui->lineEditName->text()))
    {
        QMessageBox::critical(this, tr("Error"), tr("<p align='center'>Invalid investment type name entered.<br>Please enter a valid name.</p>"), QMessageBox::Ok);
    }
    else if(!controller->verifyTargetAmount(ui->lineEditTargetAmount->text()))
    {
        QMessageBox::critical(this, tr("Error"), tr("<p align='center'>Invalid monthly target amount entered for fixed expense type.<br>Please enter a valid, non-zero amount.</p>"), QMessageBox::Ok);
    }
    else if(!controller->verifyUniqueTypeName(ui->lineEditName->text()))
    {
        QMessageBox::critical(this, tr("Error"), tr("<p align='center'>Investment type already exists.<br>Please enter a valid, unique investment type name.</p>"), QMessageBox::Ok);
    }
    else
    {
        controller->addInvestmentType(ui->lineEditName->text(), ui->lineEditTargetAmount->text().toDouble());
        QMessageBox::information(this, tr("Success"), tr("<p align='center'>Successfully added investment type.</p>"), QMessageBox::Ok);
    }
}

void AddInvestmentTypeDialog::onPushButtonUpdateTypeClicked()
{
    if(ui->comboBoxInvestmentType->currentIndex() > 0)
    {
        if(!controller->verifyTypeName(ui->lineEditName->text()))
        {
            QMessageBox::critical(this, tr("Error"), tr("<p align='center'>Invalid investment type name entered.<br>Please enter a valid name.</p>"), QMessageBox::Ok);
            return;
        }
        else if(!controller->verifyTargetAmount(ui->lineEditTargetAmount->text()))
        {
            QMessageBox::critical(this, tr("Error"), tr("<p align='center'>Invalid monthly target amount entered.<br>Please enter a valid, non-zero amount.</p>"), QMessageBox::Ok);
            return;
        }
        else
        {
            controller->updateInvestmentType(ui->comboBoxInvestmentType->currentText(), ui->lineEditName->text(), ui->lineEditTargetAmount->text().toDouble());
            QMessageBox::information(this, tr("Success"), tr("<p align='center'>Successfully updated investment type.</p>"), QMessageBox::Ok);
        }
    }
    else
    {
        QMessageBox::critical(this, tr("Error"), "<p align='center'>No investment type has been selected.<br>Please select an investment type to be updated.</p>", QMessageBox::Ok);
        return;
    }

    updateComboBox();
}

void AddInvestmentTypeDialog::onPushButtonDeleteTypeClicked()
{
    if(ui->comboBoxInvestmentType->currentIndex() > 0)
    {
        if(controller->investmentTypeContainsYearlyTransactions(ui->comboBoxInvestmentType->currentText()))
        {
            QMessageBox::critical(this, tr("Error"), "<p align='center'>The expense type '" + ui->comboBoxInvestmentType->currentText() + "' contains transactions for the current year.<br>Cannot delete selected expense type.</p>", QMessageBox::Ok);
            return;
        }
        else
        {
            int returnValue = QMessageBox::warning(this, tr("Confirm Selection"), "Are you sure you want to delete investment type '" + ui->comboBoxInvestmentType->currentText() + "'?", QMessageBox::Yes | QMessageBox::No);

            switch (returnValue)
            {
              case QMessageBox::Yes:

                  controller->deleteInvestmentType(ui->comboBoxInvestmentType->currentText());
                  QMessageBox::information(this, tr("Success"), "<p align='center'>Successfully deleted investment type '" + ui->comboBoxInvestmentType->currentText() + "'.</p>", QMessageBox::Ok);

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
        QMessageBox::critical(this, tr("Error"), "<p align='center'>No investment type has been selected.<br>Please select an investment type to be deleted.</p>", QMessageBox::Ok);
        return;
    }

    ui->comboBoxInvestmentType->setCurrentIndex(0);
    updateComboBox();
}

void AddInvestmentTypeDialog::investmentTypeSelectionChanged(QString type)
{
    if(ui->comboBoxInvestmentType->currentIndex() > 0)
    {
        ui->lineEditName->setText(type);
        ui->lineEditTargetAmount->setText(controller->getMonthlyTargetAmount(type));
    }
    else
    {
        ui->lineEditName->clear();
        ui->lineEditTargetAmount->setText("0.00");
    }
}

void AddInvestmentTypeDialog::closeEvent(QCloseEvent *)
{
    emit dialogClosed();
    accept();
}

void AddInvestmentTypeDialog::updateComboBox()
{
    ui->comboBoxInvestmentType->clear();
    ui->comboBoxInvestmentType->addItems(controller->getInvestmentTypes());
    if(ui->comboBoxInvestmentType->count() == 0)
    {
        ui->comboBoxInvestmentType->insertItem(0, "No Investment Types Found");
        disableActions();
    }
    else
    {
        ui->comboBoxInvestmentType->insertItem(0, "<Investment Types>");
    }
}

void AddInvestmentTypeDialog::disableActions()
{
    ui->lineEditName->setEnabled(false);
    ui->lineEditTargetAmount->setEnabled(false);
    ui->pushButtonAddType->setEnabled(false);
    ui->pushButtonUpdateType->setEnabled(false);
    ui->pushButtonDeleteType->setEnabled(false);
}
