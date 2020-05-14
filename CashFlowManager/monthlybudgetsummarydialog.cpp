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
    januaryExpenseTableModel(localExpenseInterface, 1, true),
    januaryInvestmentTableModel(localInvestmentInterface, 1, true),
    maxColumnWidth(0),
    tableWidth(0),
    expenseTableHeight(0),
    investmentTableHeight(0)
{
    ui->setupUi(this);
    ui->labelDialogTitle->setText(QString::number(QDate::currentDate().year()) + " Monthly Budget Summary");
    showMaximized();
    setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);
    setWindowFlag(Qt::WindowMinMaxButtonsHint);

    setTableData();

    configureTable(ui->tableViewJanuaryExpenses, januaryExpenseTableModel, true);
    configureTable(ui->tableViewJanuaryInvestments, januaryInvestmentTableModel, false);
}

MonthlyBudgetSummaryDialog::~MonthlyBudgetSummaryDialog()
{
    delete ui;
}

void MonthlyBudgetSummaryDialog::setTableData()
{
    januaryExpenseTableModel.setExpenseTypes();
    januaryInvestmentTableModel.setInvestmentTypes();
}

void MonthlyBudgetSummaryDialog::configureTable(QTableView* tableView, QAbstractTableModel& tableModel, bool isExpenseTable)
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
    tableView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

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
    if(maxColumnWidth == 0)
    {
        for(int i = 1; i < januaryExpenseTableModel.columnCount(); ++i)
        {
            tableView->resizeColumnToContents(i);
            int currentColumnWidth = tableView->columnWidth(i);
            if(currentColumnWidth > maxColumnWidth)
            {
                maxColumnWidth = currentColumnWidth;
            }
        }
    }

    tableView->setColumnWidth(1, maxColumnWidth);
    tableView->setColumnWidth(2, maxColumnWidth);
    tableView->setColumnWidth(3, maxColumnWidth);

    // Set TableView height
    if(isExpenseTable && (expenseTableHeight <= 0))
    {
        tableView->resizeRowsToContents();
        for(int i = 0; i < januaryExpenseTableModel.rowCount(); ++i)
        {
            expenseTableHeight += tableView->rowHeight(i);
        }

        expenseTableHeight += tableView->horizontalHeader()->height();
    }

    if(!isExpenseTable && (investmentTableHeight <= 0))
    {
        tableView->resizeRowsToContents();
        for(int i = 0; i < januaryInvestmentTableModel.rowCount(); ++i)
        {
            investmentTableHeight += tableView->rowHeight(i);
        }

        investmentTableHeight += tableView->horizontalHeader()->height();
    }

    if(isExpenseTable)
    {
        tableView->setMinimumHeight(expenseTableHeight);
        tableView->setMaximumHeight(expenseTableHeight);
    }
    else
    {
        tableView->setMinimumHeight(investmentTableHeight);
        tableView->setMaximumHeight(investmentTableHeight);
    }

    // Set TableView width
    if(tableWidth == 0)
    {
        for(int i = 0; i < tableView->horizontalHeader()->count(); ++i)
        {
            tableWidth += tableView->horizontalHeader()->sectionSize(i);
        }
    }

    if(tableWidth > 0)
    {
        tableView->setMinimumWidth(tableWidth);
        tableView->setMaximumWidth(tableWidth);
    }
}
