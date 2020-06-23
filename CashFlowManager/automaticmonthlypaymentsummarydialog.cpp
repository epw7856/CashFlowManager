#include "automaticmonthlypaymentsummarydialog.h"
#include <QScrollBar>
#include "ui_automaticmonthlypaymentsummarydialog.h"

AutomaticMonthlyPaymentSummaryDialog::AutomaticMonthlyPaymentSummaryDialog
(
    ExpenseInterface& localExpenseInterface,
    bool selectionEnabled,
    QWidget* parent
)
:
    QDialog(parent),
    ui(new Ui::AutomaticMonthlyPaymentSummaryDialog),
    autoPaymentTableModel(localExpenseInterface)
{
    ui->setupUi(this);
    setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);
    ui->labelDialogTitle->setText(QString("%1%2").arg(QString::number(QDate::currentDate().year())).arg(" Automatic Monthly Payment Summary"));
    ui->verticalLayout_3->setAlignment(Qt::AlignTop);
    autoPaymentTableModel.setAutomaticMonthlyPayments();

    connect(ui->pushButtonExit, &QPushButton::clicked, this, &AutomaticMonthlyPaymentSummaryDialog::onPushButtonExitClicked);

    configureAutoMonthlyPaymentTable(selectionEnabled);
}

AutomaticMonthlyPaymentSummaryDialog::~AutomaticMonthlyPaymentSummaryDialog()
{
    delete ui;
}

void AutomaticMonthlyPaymentSummaryDialog::onPushButtonExitClicked()
{
    close();
}

void AutomaticMonthlyPaymentSummaryDialog::configureAutoMonthlyPaymentTable(bool selectionEnabled)
{
    // Add table model data and disable selection
    ui->tableViewAutoPaymentSummary->setModel(&autoPaymentTableModel);
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

    if(selectionEnabled)
    {
        ui->tableViewAutoPaymentSummary->setSelectionMode(QAbstractItemView::SingleSelection);
        ui->tableViewAutoPaymentSummary->setSelectionBehavior(QAbstractItemView::SelectRows);
    }
    else
    {
        ui->tableViewAutoPaymentSummary->setSelectionMode(QAbstractItemView::NoSelection);
    }

    // Add header frame
    //ui->tableViewExpenseSummary->horizontalHeader()->setFrameStyle(QFrame::HLine);
    //ui->tableViewExpenseSummary->horizontalHeader()->setFrameShadow(QFrame::Plain);
    //ui->tableViewExpenseSummary->horizontalHeader()->setLineWidth(1);

    // Resize columns to be uniform
    ui->tableViewAutoPaymentSummary->resizeColumnsToContents();

    // Set TableView height
    int tableHeight = 0;
    ui->tableViewAutoPaymentSummary->resizeRowsToContents();
    for(int i = 0; i < autoPaymentTableModel.rowCount(); ++i)
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
