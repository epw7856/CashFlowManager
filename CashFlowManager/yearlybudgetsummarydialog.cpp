#include "expenseinterface.h"
#include "investmentinterface.h"
#include <QScrollBar>
#include <QSortFilterProxyModel>
#include "ui_yearlybudgetsummarydialog.h"
#include "yearlybudgetsummarydialog.h"

YearlyBudgetSummaryDialog::YearlyBudgetSummaryDialog
(
    ExpenseInterface& localExpenseInterface,
    InvestmentInterface& localInvestmentInterface,
    QWidget *parent
)
:
    QDialog(parent),
    ui(new Ui::YearlyBudgetSummaryDialog),
    expenseTableModel(localExpenseInterface),
    investmentTableModel(localInvestmentInterface)
{
    ui->setupUi(this);
    setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);
    ui->labelDialogTitle->setText(QString("%1%2").arg(QString::number(QDate::currentDate().year())).arg(" Yearly Budget Summary"));
    ui->verticalLayout_3->setAlignment(Qt::AlignTop);
    ui->verticalLayout_4->setAlignment(Qt::AlignTop);
    expenseTableModel.setExpenseTypes();
    investmentTableModel.setInvestmentTypes();

    connect(ui->pushButtonExit, &QPushButton::clicked, this, &YearlyBudgetSummaryDialog::onPushButtonExitClicked);

    configureExpenseSummaryTable();
    configureInvestmentSummaryTable();
}

YearlyBudgetSummaryDialog::~YearlyBudgetSummaryDialog()
{
    delete ui;
}

void YearlyBudgetSummaryDialog::onPushButtonExitClicked()
{
    close();
}

void YearlyBudgetSummaryDialog::configureExpenseSummaryTable()
{
    QSortFilterProxyModel* expenseProxyModel = new QSortFilterProxyModel;
    expenseProxyModel->setSourceModel(&expenseTableModel);
    expenseProxyModel->setSortRole(Qt::EditRole);

    // Add table model data and disable selection
    ui->tableViewExpenseSummary->setModel(expenseProxyModel);
    ui->tableViewExpenseSummary->setSelectionMode(QAbstractItemView::NoSelection);
    ui->tableViewExpenseSummary->sortByColumn(2, Qt::DescendingOrder);
    ui->tableViewExpenseSummary->setSortingEnabled(true);

    // Set bold font for the header
    QFont font(ui->tableViewExpenseSummary->font());
    font.setBold(true);
    ui->tableViewExpenseSummary->horizontalHeader()->setFont(font);

    // Disable horizontal scroll bar
    ui->tableViewExpenseSummary->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    // Disable cell resizing and selections
    ui->tableViewExpenseSummary->horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed);
    ui->tableViewExpenseSummary->horizontalHeader()->setFixedHeight(25);
    ui->tableViewExpenseSummary->verticalHeader()->setSectionResizeMode(QHeaderView::Fixed);
    ui->tableViewExpenseSummary->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableViewExpenseSummary->setFocusPolicy(Qt::NoFocus);
    ui->tableViewExpenseSummary->setSelectionMode(QAbstractItemView::NoSelection);

    // Add header frame
    //ui->tableViewExpenseSummary->horizontalHeader()->setFrameStyle(QFrame::HLine);
    //ui->tableViewExpenseSummary->horizontalHeader()->setFrameShadow(QFrame::Plain);
    //ui->tableViewExpenseSummary->horizontalHeader()->setLineWidth(1);

    // Resize columns to be uniform
    int maxColumnWidth = 0;
    for(int i = 1; i < expenseTableModel.columnCount(); ++i)
    {
        ui->tableViewExpenseSummary->resizeColumnToContents(i);
        int currentColumnWidth = ui->tableViewExpenseSummary->columnWidth(i);
        if(currentColumnWidth > maxColumnWidth)
        {
            maxColumnWidth = currentColumnWidth;
        }
    }

    ui->tableViewExpenseSummary->setColumnWidth(1, maxColumnWidth);
    ui->tableViewExpenseSummary->setColumnWidth(2, maxColumnWidth);

    // Set TableView height
    int tableHeight = 0;
    ui->tableViewInvestmentSummary->resizeRowsToContents();
    for(int i = 0; i < expenseTableModel.rowCount(); ++i)
    {
        tableHeight += ui->tableViewExpenseSummary->rowHeight(i);
    }

    tableHeight += ui->tableViewExpenseSummary->horizontalHeader()->height();
    tableHeight += 5;
    ui->tableViewExpenseSummary->setMaximumHeight(tableHeight);
    ui->groupBoxExpenseBudget->setMaximumHeight(tableHeight + 40);

    // Set TableView width
    int tableWidth = 0;
    for(int i = 0; i < ui->tableViewExpenseSummary->horizontalHeader()->count(); ++i)
    {
        tableWidth += ui->tableViewExpenseSummary->horizontalHeader()->sectionSize(i);
    }

    if(ui->tableViewExpenseSummary->verticalScrollBar()->width() < 100)
    {
        tableWidth += ui->tableViewExpenseSummary->verticalScrollBar()->width();
    }

    ui->tableViewExpenseSummary->setMinimumWidth(tableWidth);
    ui->tableViewExpenseSummary->setMaximumWidth(tableWidth);
}

void YearlyBudgetSummaryDialog::configureInvestmentSummaryTable()
{
    QSortFilterProxyModel* investmentProxyModel = new QSortFilterProxyModel;
    investmentProxyModel->setSourceModel(&investmentTableModel);
    investmentProxyModel->setSortRole(Qt::EditRole);

    // Add table model data and disable selection
    ui->tableViewInvestmentSummary->setModel(investmentProxyModel);
    ui->tableViewInvestmentSummary->setSelectionMode(QAbstractItemView::NoSelection);
    ui->tableViewInvestmentSummary->sortByColumn(2, Qt::DescendingOrder);
    ui->tableViewInvestmentSummary->setSortingEnabled(true);

    // Set bold font for the header
    QFont font(ui->tableViewInvestmentSummary->font());
    font.setBold(true);
    ui->tableViewInvestmentSummary->horizontalHeader()->setFont(font);

    // Disable horizontal scroll bar
    ui->tableViewInvestmentSummary->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    // Disable cell resizing and selections
    ui->tableViewInvestmentSummary->horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed);
    ui->tableViewInvestmentSummary->horizontalHeader()->setFixedHeight(25);
    ui->tableViewInvestmentSummary->verticalHeader()->setSectionResizeMode(QHeaderView::Fixed);
    ui->tableViewInvestmentSummary->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableViewInvestmentSummary->setFocusPolicy(Qt::NoFocus);
    ui->tableViewInvestmentSummary->setSelectionMode(QAbstractItemView::NoSelection);

    // Add header frame
    //ui->tableViewInvestmentSummary->horizontalHeader()->setFrameStyle(QFrame::HLine);
    //ui->tableViewInvestmentSummary->horizontalHeader()->setFrameShadow(QFrame::Plain);
    //ui->tableViewInvestmentSummary->horizontalHeader()->setLineWidth(1);

    // Resize columns to be uniform
    int maxColumnWidth = 0;
    ui->tableViewInvestmentSummary->resizeColumnsToContents();
    for(int i = 1; i < investmentTableModel.columnCount(); ++i)
    {
        int currentColumnWidth = ui->tableViewInvestmentSummary->columnWidth(i);
        if(currentColumnWidth > maxColumnWidth)
        {
            maxColumnWidth = currentColumnWidth;
        }
    }

    ui->tableViewInvestmentSummary->setColumnWidth(1, maxColumnWidth);
    ui->tableViewInvestmentSummary->setColumnWidth(2, maxColumnWidth);

    // Set TableView height
    int tableHeight = 0;
    ui->tableViewInvestmentSummary->resizeRowsToContents();
    for(int i = 0; i < investmentTableModel.rowCount(); ++i)
    {
        tableHeight += ui->tableViewInvestmentSummary->rowHeight(i);
    }

    tableHeight += ui->tableViewInvestmentSummary->horizontalHeader()->height();
    tableHeight += 5;
    ui->tableViewInvestmentSummary->setMaximumHeight(tableHeight);
    ui->groupBoxInvestmentBudget->setMaximumHeight(tableHeight + 40);

    // Set TableView width
    int tableWidth = 0;
    for(int i = 0; i < ui->tableViewInvestmentSummary->horizontalHeader()->count(); ++i)
    {
        tableWidth += ui->tableViewInvestmentSummary->horizontalHeader()->sectionSize(i);
    }

    if(ui->tableViewInvestmentSummary->verticalScrollBar()->width() < 100)
    {
        tableWidth += ui->tableViewInvestmentSummary->verticalScrollBar()->width();
    }

    ui->tableViewInvestmentSummary->setMinimumWidth(tableWidth);
    ui->tableViewInvestmentSummary->setMaximumWidth(tableWidth);
}
