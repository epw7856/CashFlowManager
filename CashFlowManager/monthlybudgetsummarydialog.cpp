#include "dateutilities.h"
#include "expenseinterface.h"
#include "investmentinterface.h"
#include "monthlybudgetsummarydialog.h"
#include <QScrollBar>
#include "ui_monthlybudgetsummarydialog.h"

MonthlyBudgetSummaryDialog::MonthlyBudgetSummaryDialog
(
    ExpenseInterface& localExpenseInterface,
    InvestmentInterface& localInvestmentInterface,
    QWidget* parent
)
:
    QDialog(parent),
    ui(new Ui::MonthlyBudgetSummaryDialog),
    januaryExpenseTableModel(localExpenseInterface, DateUtilities::getMonthlyDates(1)),
    januaryInvestmentTableModel(localInvestmentInterface, DateUtilities::getMonthlyDates(1))
{
    ui->setupUi(this);
    showMaximized();
    setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);
    setWindowFlag(Qt::WindowMinMaxButtonsHint);
    januaryExpenseTableModel.setExpenseTypes();
    januaryInvestmentTableModel.setInvestmentTypes();

    configureTable(ui->tableViewJanuaryExpenses, januaryExpenseTableModel);
    configureTable(ui->tableViewJanuaryInvestments, januaryInvestmentTableModel);
}

MonthlyBudgetSummaryDialog::~MonthlyBudgetSummaryDialog()
{
    delete ui;
}

void MonthlyBudgetSummaryDialog::configureTable(QTableView* tableView, QAbstractTableModel& tableModel)
{
    // Add table model data and disable selection
    tableView->setModel(&tableModel);
    tableView->setSelectionMode(QAbstractItemView::NoSelection);

    // Set bold font for the header
    QFont font(tableView->font());
    font.setBold(true);
    tableView->horizontalHeader()->setFont(font);

    // Disable horizontal scroll bar
    tableView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    // Disable cell resizing and selections
    tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed);
    tableView->horizontalHeader()->setFixedHeight(25);
    tableView->verticalHeader()->setSectionResizeMode(QHeaderView::Fixed);
    tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    tableView->setFocusPolicy(Qt::NoFocus);
    tableView->setSelectionMode(QAbstractItemView::NoSelection);

    // Add header frame
    //ui->tableViewExpenseSummary->horizontalHeader()->setFrameStyle(QFrame::HLine);
    //ui->tableViewExpenseSummary->horizontalHeader()->setFrameShadow(QFrame::Plain);
    //ui->tableViewExpenseSummary->horizontalHeader()->setLineWidth(1);

    // Resize columns to be uniform
    int maxColumnWidth = 0;
    for(int i = 1; i < januaryExpenseTableModel.columnCount(); ++i)
    {
        tableView->resizeColumnToContents(i);
        int currentColumnWidth = tableView->columnWidth(i);
        if(currentColumnWidth > maxColumnWidth)
        {
            maxColumnWidth = currentColumnWidth;
        }
    }

    tableView->setColumnWidth(1, maxColumnWidth);
    tableView->setColumnWidth(2, maxColumnWidth);

    // Set TableView height
    int tableHeight = 0;
    tableView->resizeRowsToContents();
    for(int i = 0; i < januaryExpenseTableModel.rowCount(); ++i)
    {
        tableHeight += tableView->rowHeight(i);
    }

    tableHeight += tableView->horizontalHeader()->height();
    tableView->setMaximumHeight(tableHeight+5);

    // Set TableView width
    int tableWidth = 0;
    for(int i = 0; i < tableView->horizontalHeader()->count(); ++i)
    {
        tableWidth += tableView->horizontalHeader()->sectionSize(i);
    }

    if(tableView->verticalScrollBar()->width() < 100)
    {
        tableWidth += tableView->verticalScrollBar()->width();
    }

    tableView->setMinimumWidth(tableWidth);
    tableView->setMaximumWidth(tableWidth);
}

void MonthlyBudgetSummaryDialog::configureJanuaryTables()
{
    // Add table model data and disable selection
    ui->tableViewJanuaryExpenses->setModel(&januaryExpenseTableModel);
    ui->tableViewJanuaryExpenses->setSelectionMode(QAbstractItemView::NoSelection);

    // Set bold font for the header
    QFont font(ui->tableViewJanuaryExpenses->font());
    font.setBold(true);
    ui->tableViewJanuaryExpenses->horizontalHeader()->setFont(font);

    // Disable horizontal scroll bar
    ui->tableViewJanuaryExpenses->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    // Disable cell resizing and selections
    ui->tableViewJanuaryExpenses->horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed);
    ui->tableViewJanuaryExpenses->horizontalHeader()->setFixedHeight(25);
    ui->tableViewJanuaryExpenses->verticalHeader()->setSectionResizeMode(QHeaderView::Fixed);
    ui->tableViewJanuaryExpenses->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableViewJanuaryExpenses->setFocusPolicy(Qt::NoFocus);
    ui->tableViewJanuaryExpenses->setSelectionMode(QAbstractItemView::NoSelection);

    // Add header frame
    //ui->tableViewExpenseSummary->horizontalHeader()->setFrameStyle(QFrame::HLine);
    //ui->tableViewExpenseSummary->horizontalHeader()->setFrameShadow(QFrame::Plain);
    //ui->tableViewExpenseSummary->horizontalHeader()->setLineWidth(1);

    // Resize columns to be uniform
    int maxColumnWidth = 0;
    for(int i = 1; i < januaryExpenseTableModel.columnCount(); ++i)
    {
        ui->tableViewJanuaryExpenses->resizeColumnToContents(i);
        int currentColumnWidth = ui->tableViewJanuaryExpenses->columnWidth(i);
        if(currentColumnWidth > maxColumnWidth)
        {
            maxColumnWidth = currentColumnWidth;
        }
    }

    ui->tableViewJanuaryExpenses->setColumnWidth(1, maxColumnWidth);
    ui->tableViewJanuaryExpenses->setColumnWidth(2, maxColumnWidth);

    // Set TableView height
    int tableHeight = 0;
    ui->tableViewJanuaryExpenses->resizeRowsToContents();
    for(int i = 0; i < januaryExpenseTableModel.rowCount(); ++i)
    {
        tableHeight += ui->tableViewJanuaryExpenses->rowHeight(i);
    }

    tableHeight += ui->tableViewJanuaryExpenses->horizontalHeader()->height();
    ui->tableViewJanuaryExpenses->setMaximumHeight(tableHeight+5);

    // Set TableView width
    int tableWidth = 0;
    for(int i = 0; i < ui->tableViewJanuaryExpenses->horizontalHeader()->count(); ++i)
    {
        tableWidth += ui->tableViewJanuaryExpenses->horizontalHeader()->sectionSize(i);
    }

    if(ui->tableViewJanuaryExpenses->verticalScrollBar()->width() < 100)
    {
        tableWidth += ui->tableViewJanuaryExpenses->verticalScrollBar()->width();
    }

    ui->tableViewJanuaryExpenses->setMinimumWidth(tableWidth);
    ui->tableViewJanuaryExpenses->setMaximumWidth(tableWidth);
}
