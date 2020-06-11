#include "currencyutilities.h"
#include "mortgageinterface.h"
#include "mortgagesummarydialog.h"
#include <QScrollBar>
#include "ui_mortgagesummarydialog.h"

MortgageSummaryDialog::MortgageSummaryDialog(MortgageInterface& localMortgageInterface, QWidget* parent) :
    QDialog(parent),
    ui(new Ui::MortgageSummaryDialog),
    mortgageTableModel(localMortgageInterface)
{
    ui->setupUi(this);
    setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);
    setWindowFlag(Qt::WindowMinMaxButtonsHint);
    showMaximized();
    mortgageTableModel.setMortgageInformation();

    ui->labelLoanAmount->setText(QString::fromStdString(CurrencyUtilities::formatCurrency(localMortgageInterface.getTotalLoanAmount())));
    ui->labelRemainingBalance->setText(QString::fromStdString(CurrencyUtilities::formatCurrency(mortgageTableModel.getRemainingLoanBalance())));
    ui->labelMarketValue->setText(QString::fromStdString(CurrencyUtilities::formatCurrency(localMortgageInterface.getMarketValue())));
    ui->labelInterestRate->setText(QString::fromStdString(CurrencyUtilities::formatRatio(localMortgageInterface.getInterestRate(), 3)));
    ui->labelTerm->setText(QString::number(localMortgageInterface.getLoanTerm()) + " years");
    ui->labelBasePayment->setText(QString::fromStdString(CurrencyUtilities::formatCurrency(localMortgageInterface.getBasePayment())));

    connect(ui->pushButtonExit, &QPushButton::clicked, this, &MortgageSummaryDialog::onPushButtonExitClicked);

    configureMortgageSummaryTable();
}

MortgageSummaryDialog::~MortgageSummaryDialog()
{
    delete ui;
}

void MortgageSummaryDialog::onPushButtonExitClicked()
{
    close();
}

void MortgageSummaryDialog::configureMortgageSummaryTable()
{
    // Add table model data and disable selection
    ui->tableViewMortgageSummary->setModel(&mortgageTableModel);
    ui->tableViewMortgageSummary->setSelectionMode(QAbstractItemView::NoSelection);

    // Set bold font for the header
    QFont font(ui->tableViewMortgageSummary->font());
    font.setBold(true);
    ui->tableViewMortgageSummary->horizontalHeader()->setFont(font);

    // Disable horizontal scroll bar
    ui->tableViewMortgageSummary->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->tableViewMortgageSummary->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    // Disable cell resizing and selections
    ui->tableViewMortgageSummary->horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed);
    ui->tableViewMortgageSummary->horizontalHeader()->setFixedHeight(25);
    ui->tableViewMortgageSummary->verticalHeader()->setSectionResizeMode(QHeaderView::Fixed);
    ui->tableViewMortgageSummary->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableViewMortgageSummary->setFocusPolicy(Qt::NoFocus);
    ui->tableViewMortgageSummary->setSelectionMode(QAbstractItemView::NoSelection);

    // Add header frame
    //ui->tableViewExpenseSummary->horizontalHeader()->setFrameStyle(QFrame::HLine);
    //ui->tableViewExpenseSummary->horizontalHeader()->setFrameShadow(QFrame::Plain);
    //ui->tableViewExpenseSummary->horizontalHeader()->setLineWidth(1);

    // Resize columns to be uniform
    ui->tableViewMortgageSummary->resizeColumnsToContents();
    int maxColumnWidth = 0;
    for(int i = 2; i < 7; ++i)
    {
        int currentColumnWidth = ui->tableViewMortgageSummary->columnWidth(i);
        if(currentColumnWidth > maxColumnWidth)
        {
            maxColumnWidth = currentColumnWidth;
        }
    }

    for(int i = 2; i < 7; ++i)
    {
        ui->tableViewMortgageSummary->setColumnWidth(i, maxColumnWidth);
    }

    // Set TableView height
    int tableHeight = 0;
    ui->tableViewMortgageSummary->resizeRowsToContents();
    for(int i = 0; i < mortgageTableModel.rowCount(); ++i)
    {
        tableHeight += ui->tableViewMortgageSummary->rowHeight(i);
    }

    tableHeight += ui->tableViewMortgageSummary->horizontalHeader()->height();
    ui->tableViewMortgageSummary->setMaximumHeight(tableHeight+5);
    ui->tableViewMortgageSummary->setMinimumHeight(tableHeight+5);

    // Set TableView width
    int tableWidth = 0;
    for(int i = 0; i < ui->tableViewMortgageSummary->horizontalHeader()->count(); ++i)
    {
        tableWidth += ui->tableViewMortgageSummary->horizontalHeader()->sectionSize(i);
    }

    if(ui->tableViewMortgageSummary->verticalScrollBar()->width() < 100)
    {
        tableWidth += ui->tableViewMortgageSummary->verticalScrollBar()->width();
    }

    ui->tableViewMortgageSummary->setMinimumWidth(tableWidth);
    ui->tableViewMortgageSummary->setMaximumWidth(tableWidth);

    if(ui->scrollArea->verticalScrollBar()->width() < 100)
    {
        tableWidth += ui->scrollArea->verticalScrollBar()->width();
    }

    ui->scrollArea->setMinimumWidth(tableWidth + 20);
    ui->scrollArea->setMaximumWidth(tableWidth + 20);
}
