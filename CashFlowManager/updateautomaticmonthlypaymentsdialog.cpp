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
    }
    else if(!controller->verifyPaymentDescription(ui->lineEditDescription->text()))
    {
        QMessageBox::critical(this, tr("Error"), tr("<p align='center'>Invalid payment description entered.<br>Please enter a valid description.</p>"), QMessageBox::Ok);
    }
    else if(!controller->verifyTransactionAmount(ui->lineEditAmount->text()))
    {
        QMessageBox::critical(this, tr("Error"), tr("<p align='center'>Invalid payment amount entered.<br>Please enter a valid non-zero amount.</p>"), QMessageBox::Ok);
    }
    else
    {
        controller->addAutomaticMonthlyPayment(ui->lineEditAccount->text(),
                                               ui->lineEditDescription->text(),
                                               ui->lineEditAmount->text().remove(',').toDouble());

        QMessageBox::information(this, tr("Success"), tr("<p align='center'>Successfully added automatic monthly payment.</p>"), QMessageBox::Ok);
    }

    configurePaymentTable();
}

void UpdateAutomaticMonthlyPaymentsDialog::onPushButtonUpdatePaymentClicked()
{

}

void UpdateAutomaticMonthlyPaymentsDialog::onPushButtonDeletePaymentClicked()
{
    QModelIndexList index = ui->tableViewAutoPaymentSummary->selectionModel()->selection().indexes();
    QString test = index.at(0).data().toString();
    QString test2 = index.at(1).data().toString();
    QString test3 = index.at(2).data().toString();
    if(index.count() == 0)
    {
        int test = 1;
    }
    else if(index.count() == 1)
    {
        int test = 2;
    }
    else
    {
        int test = 3;
    }
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

    // Disable scroll bars
    ui->tableViewAutoPaymentSummary->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->tableViewAutoPaymentSummary->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    // Disable cell resizing and selections
    ui->tableViewAutoPaymentSummary->horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed);
    ui->tableViewAutoPaymentSummary->horizontalHeader()->setFixedHeight(25);
    ui->tableViewAutoPaymentSummary->verticalHeader()->setSectionResizeMode(QHeaderView::Fixed);
    ui->tableViewAutoPaymentSummary->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableViewAutoPaymentSummary->setFocusPolicy(Qt::NoFocus);

    // Add header frame
    //ui->tableViewExpenseSummary->horizontalHeader()->setFrameStyle(QFrame::HLine);
    //ui->tableViewExpenseSummary->horizontalHeader()->setFrameShadow(QFrame::Plain);
    //ui->tableViewExpenseSummary->horizontalHeader()->setLineWidth(1);

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

    if(ui->tableViewAutoPaymentSummary->verticalScrollBar()->width() < 100)
    {
        tableWidth += ui->tableViewAutoPaymentSummary->verticalScrollBar()->width();
    }

    ui->tableViewAutoPaymentSummary->setMinimumWidth(tableWidth);
    ui->tableViewAutoPaymentSummary->setMaximumWidth(tableWidth);
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
    ui->tableViewAutoPaymentSummary->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableViewAutoPaymentSummary->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->pushButtonAddPayment->setEnabled(false);
    ui->pushButtonDeletePayment->setEnabled(true);
    ui->pushButtonUpdatePayment->setEnabled(true);
    ui->pushButtonUpdatePayment->setFocus();
    ui->lineEditAccount->clear();
    ui->lineEditDescription->clear();
    ui->lineEditAmount->clear();
    ui->lineEditAmount->setText("0.00");
}

void UpdateAutomaticMonthlyPaymentsDialog::fillFields()
{
    ui->lineEditAccount->clear();
    ui->lineEditDescription->clear();
    ui->lineEditAmount->clear();

    if(!ui->radioButtonAdd->isChecked())
    {
        QModelIndexList index = ui->tableViewAutoPaymentSummary->selectionModel()->selectedRows();
        ui->lineEditAccount->setText(index.at(0).data().toString());
        ui->lineEditDescription->setText(index.at(1).data().toString());
        ui->lineEditAmount->setText(index.at(2).data().toString().remove('$'));
    }
}
