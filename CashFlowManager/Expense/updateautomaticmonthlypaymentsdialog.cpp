#include <QMessageBox>
#include <QScrollBar>
#include "updateautomaticmonthlypaymentsdialog.h"
#include "updateautomaticmonthlypaymentsdialogcontroller.h"
#include "ui_updateautomaticmonthlypaymentsdialog.h"

UpdateAutomaticMonthlyPaymentsDialog::UpdateAutomaticMonthlyPaymentsDialog(ExpenseInterface& localExpenseInterface, QWidget* parent) :
    QDialog(parent),
    ui(new Ui::UpdateAutomaticMonthlyPaymentsDialog),
    paymentTable(localExpenseInterface),
    controller(std::make_unique<UpdateAutomaticMonthlyPaymentsDialogController>(localExpenseInterface))
{
    ui->setupUi(this);
    setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);
    setWindowFlag(Qt::WindowMinMaxButtonsHint);

    connect(ui->pushButtonExit, &QPushButton::clicked, this, &UpdateAutomaticMonthlyPaymentsDialog::onPushButtonExitClicked);
    connect(ui->pushButtonAddPayment, &QPushButton::clicked, this, &UpdateAutomaticMonthlyPaymentsDialog::onPushButtonAddPaymentClicked);
    connect(ui->pushButtonUpdatePayment, &QPushButton::clicked, this, &UpdateAutomaticMonthlyPaymentsDialog::onPushButtonUpdatePaymentClicked);
    connect(ui->pushButtonDeletePayment, &QPushButton::clicked, this, &UpdateAutomaticMonthlyPaymentsDialog::onPushButtonDeletePaymentClicked);
    connect(ui->radioButtonAdd, &QRadioButton::toggled, this, &UpdateAutomaticMonthlyPaymentsDialog::onRadioButtonToggled);
    connect(ui->tableViewAutoPaymentSummary, &QTableView::clicked, this, &UpdateAutomaticMonthlyPaymentsDialog::fillFields);

    enableAddPayment();
    configurePaymentTable();
}

UpdateAutomaticMonthlyPaymentsDialog::~UpdateAutomaticMonthlyPaymentsDialog()
{
    delete ui;
}

void UpdateAutomaticMonthlyPaymentsDialog::onPushButtonExitClicked()
{
    close();
}

void UpdateAutomaticMonthlyPaymentsDialog::onPushButtonAddPaymentClicked()
{
    if(!controller->verifyAccountName(ui->lineEditAccount->text()))
    {
        QMessageBox::critical(this, tr("Error"), tr("<p align='center'>Invalid account name entered.<br>Please enter a valid account.</p>"), QMessageBox::Ok);
        return;
    }
    else if(!controller->verifyPaymentDescription(ui->lineEditDescription->text()))
    {
        QMessageBox::critical(this, tr("Error"), tr("<p align='center'>Invalid payment description entered.<br>Please enter a valid description.</p>"), QMessageBox::Ok);
        return;
    }
    else if(!controller->verifyTransactionAmount(ui->lineEditAmount->text()))
    {
        QMessageBox::critical(this, tr("Error"), tr("<p align='center'>Invalid payment amount entered.<br>Please enter a valid non-zero amount.</p>"), QMessageBox::Ok);
        return;
    }
    else if(!controller->verifyUniquePaymentName(ui->lineEditAccount->text(), ui->lineEditDescription->text()))
    {
        QMessageBox::critical(this, tr("Error"), tr("<p align='center'>Unable to add automatic monthly payment. Payment already exists.</p>"), QMessageBox::Ok);
        return;
    }
    else
    {
        controller->addAutomaticMonthlyPayment(ui->lineEditAccount->text(),
                                               ui->lineEditDescription->text(),
                                               ui->lineEditAmount->text().remove(',').toDouble());

        QMessageBox::information(this, tr("Success"), tr("<p align='center'>Successfully added automatic monthly payment.</p>"), QMessageBox::Ok);
    }

    configurePaymentTable();
    enableAddPayment();
}

void UpdateAutomaticMonthlyPaymentsDialog::onPushButtonUpdatePaymentClicked()
{
    bool changesPresent = (existingDescription != ui->lineEditDescription->text()) ||
                          (existingAccount != ui->lineEditAccount->text()) ||
                          (existingAmount != ui->lineEditAmount->text());

    if(!controller->verifyAccountName(ui->lineEditAccount->text()))
    {
        QMessageBox::critical(this, tr("Error"), tr("<p align='center'>Invalid account name entered.<br>Please enter a valid account.</p>"), QMessageBox::Ok);
        return;
    }
    else if(!controller->verifyPaymentDescription(ui->lineEditDescription->text()))
    {
        QMessageBox::critical(this, tr("Error"), tr("<p align='center'>Invalid payment description entered.<br>Please enter a valid description.</p>"), QMessageBox::Ok);
        return;
    }
    else if(!controller->verifyTransactionAmount(ui->lineEditAmount->text()))
    {
        QMessageBox::critical(this, tr("Error"), tr("<p align='center'>Invalid payment amount entered.<br>Please enter a valid non-zero amount.</p>"), QMessageBox::Ok);
        return;
    }
    else if(!changesPresent)
    {
        QMessageBox::critical(this, tr("Error"), tr("<p align='center'>No changes detected.</p>"), QMessageBox::Ok);
        return;
    }
    else if(!controller->verifyUniquePaymentName(ui->lineEditAccount->text(), ui->lineEditDescription->text()))
    {
        QMessageBox::critical(this, tr("Error"), tr("<p align='center'>Unable to update automatic monthly payment. Another payment with the same information already exists.</p>"), QMessageBox::Ok);
        return;
    }
    else
    {
        controller->updateAutomaticMonthlyPayment(existingAccount,
                                                  existingDescription,
                                                  existingAmount.remove(',').toDouble(),
                                                  ui->lineEditAccount->text(),
                                                  ui->lineEditDescription->text(),
                                                  ui->lineEditAmount->text().remove(',').toDouble());

        QMessageBox::information(this, tr("Success"), tr("<p align='center'>Successfully updated automatic monthly payment.</p>"), QMessageBox::Ok);
    }

    configurePaymentTable();
    enableUpdatePayment();
}

void UpdateAutomaticMonthlyPaymentsDialog::onPushButtonDeletePaymentClicked()
{
    if((!controller->verifyAccountName(ui->lineEditAccount->text())) ||
       (!controller->verifyPaymentDescription(ui->lineEditDescription->text())) ||
       (!controller->verifyTransactionAmount(ui->lineEditAmount->text())))
    {
        QMessageBox::critical(this, tr("Error"), tr("<p align='center'>No selection made.<br>Please please an automatic monthly payment from the table.</p>"), QMessageBox::Ok);
        return;
    }

    controller->deleteAutomaticMonthlyPayment(ui->lineEditAccount->text(),
                                              ui->lineEditDescription->text(),
                                              ui->lineEditAmount->text().remove(',').toDouble());

    QMessageBox::information(this, tr("Success"), tr("<p align='center'>Successfully deleted automatic monthly payment.</p>"), QMessageBox::Ok);

    configurePaymentTable();
    enableUpdatePayment();
}

void UpdateAutomaticMonthlyPaymentsDialog::onRadioButtonToggled()
{
    (ui->radioButtonAdd->isChecked()) ? enableAddPayment() : enableUpdatePayment();
}

void UpdateAutomaticMonthlyPaymentsDialog::closeEvent(QCloseEvent*)
{
    emit dialogClosed();
    accept();
}

void UpdateAutomaticMonthlyPaymentsDialog::configurePaymentTable()
{
    paymentTable.setAutomaticMonthlyPayments();

    // Add table model data and disable selection
    ui->tableViewAutoPaymentSummary->setModel(&paymentTable);
    ui->tableViewAutoPaymentSummary->setSelectionMode(QAbstractItemView::NoSelection);

    // Set bold font for the header
    QFont font(ui->tableViewAutoPaymentSummary->font());
    font.setBold(true);
    ui->tableViewAutoPaymentSummary->horizontalHeader()->setFont(font);
    ui->tableViewAutoPaymentSummary->setStyleSheet("QHeaderView::section { background-color: rgb(240, 240, 240) }");

    // Disable scroll bars
    ui->tableViewAutoPaymentSummary->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->tableViewAutoPaymentSummary->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    // Disable cell resizing and selections
    ui->tableViewAutoPaymentSummary->horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed);
    ui->tableViewAutoPaymentSummary->horizontalHeader()->setFixedHeight(25);
    ui->tableViewAutoPaymentSummary->verticalHeader()->setSectionResizeMode(QHeaderView::Fixed);
    ui->tableViewAutoPaymentSummary->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableViewAutoPaymentSummary->setFocusPolicy(Qt::NoFocus);

    // Resize columns to be uniform
    ui->tableViewAutoPaymentSummary->resizeColumnsToContents();

    // Set TableView height
    int tableHeight = 0;
    ui->tableViewAutoPaymentSummary->resizeRowsToContents();
    for(int i = 0; i < paymentTable.rowCount(); ++i)
    {
        tableHeight += ui->tableViewAutoPaymentSummary->rowHeight(i);
    }

    tableHeight += ui->tableViewAutoPaymentSummary->horizontalHeader()->height();
    ui->tableViewAutoPaymentSummary->setMinimumHeight(tableHeight+5);
    ui->tableViewAutoPaymentSummary->setMaximumHeight(tableHeight+5);

    // Set TableView width
    int tableWidth = 0;
    for(int i = 0; i < ui->tableViewAutoPaymentSummary->horizontalHeader()->count(); ++i)
    {
        tableWidth += ui->tableViewAutoPaymentSummary->horizontalHeader()->sectionSize(i);
    }

    ui->tableViewAutoPaymentSummary->setMinimumWidth(tableWidth + 6);
    ui->tableViewAutoPaymentSummary->setMaximumWidth(tableWidth + 6);
}

void UpdateAutomaticMonthlyPaymentsDialog::enableAddPayment()
{
    ui->tableViewAutoPaymentSummary->clearSelection();
    ui->tableViewAutoPaymentSummary->setSelectionMode(QAbstractItemView::NoSelection);
    ui->pushButtonAddPayment->setEnabled(true);
    ui->pushButtonAddPayment->setFocus();
    ui->pushButtonDeletePayment->setEnabled(false);
    ui->pushButtonUpdatePayment->setEnabled(false);
    ui->lineEditAccount->clear();
    ui->lineEditDescription->clear();
    ui->lineEditAmount->clear();
    ui->lineEditAmount->setText("0.00");
}

void UpdateAutomaticMonthlyPaymentsDialog::enableUpdatePayment()
{
    ui->tableViewAutoPaymentSummary->clearSelection();
    ui->tableViewAutoPaymentSummary->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableViewAutoPaymentSummary->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->pushButtonAddPayment->setEnabled(false);
    ui->pushButtonDeletePayment->setEnabled(true);
    ui->pushButtonUpdatePayment->setEnabled(true);
    ui->pushButtonUpdatePayment->setFocus();
    ui->lineEditAccount->clear();
    ui->lineEditDescription->clear();
    ui->lineEditAmount->clear();
}

void UpdateAutomaticMonthlyPaymentsDialog::fillFields()
{   
    if(!ui->radioButtonAdd->isChecked())
    {
        ui->lineEditAccount->clear();
        ui->lineEditDescription->clear();
        ui->lineEditAmount->clear();

        if(ui->tableViewAutoPaymentSummary->currentIndex().row() < paymentTable.rowCount() - 2)
        {
            QModelIndexList indices = ui->tableViewAutoPaymentSummary->selectionModel()->selection().indexes();

            existingAccount = indices.at(0).data().toString();
            existingDescription = indices.at(1).data().toString();
            existingAmount = indices.at(2).data().toString().remove('$');

            ui->lineEditAccount->setText(existingAccount);
            ui->lineEditDescription->setText(existingDescription);
            ui->lineEditAmount->setText(existingAmount);
        }
    }
}
