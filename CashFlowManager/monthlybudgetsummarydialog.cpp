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
    februaryExpenseTableModel(localExpenseInterface, 2, true),
    marchExpenseTableModel(localExpenseInterface, 3, true),
    aprilExpenseTableModel(localExpenseInterface, 4, true),
    mayExpenseTableModel(localExpenseInterface, 5, true),
    juneExpenseTableModel(localExpenseInterface, 6, true),
    julyExpenseTableModel(localExpenseInterface, 7, true),
    augustExpenseTableModel(localExpenseInterface, 8, true),
    septemberExpenseTableModel(localExpenseInterface, 9, true),
    octoberExpenseTableModel(localExpenseInterface, 10, true),
    novemberExpenseTableModel(localExpenseInterface, 11, true),
    decemberExpenseTableModel(localExpenseInterface, 12, true),
    januaryInvestmentTableModel(localInvestmentInterface, 1, true),
    februaryInvestmentTableModel(localInvestmentInterface, 2, true),
    marchInvestmentTableModel(localInvestmentInterface, 3, true),
    aprilInvestmentTableModel(localInvestmentInterface, 4, true),
    mayInvestmentTableModel(localInvestmentInterface, 5, true),
    juneInvestmentTableModel(localInvestmentInterface, 6, true),
    julyInvestmentTableModel(localInvestmentInterface, 7, true),
    augustInvestmentTableModel(localInvestmentInterface, 8, true),
    septemberInvestmentTableModel(localInvestmentInterface, 9, true),
    octoberInvestmentTableModel(localInvestmentInterface, 10, true),
    novemberInvestmentTableModel(localInvestmentInterface, 11, true),
    decemberInvestmentTableModel(localInvestmentInterface, 12, true),
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

    connect(ui->pushButtonExit, &QPushButton::clicked, this, &MonthlyBudgetSummaryDialog::onPushButtonExitClicked);

    setTableData();

    configureTable(ui->tableViewJanuaryExpenses, januaryExpenseTableModel, true);
    configureTable(ui->tableViewFebruaryExpenses, februaryExpenseTableModel, true);
    configureTable(ui->tableViewMarchExpenses, marchExpenseTableModel, true);
    configureTable(ui->tableViewAprilExpenses, aprilExpenseTableModel, true);
    configureTable(ui->tableViewMayExpenses, mayExpenseTableModel, true);
    configureTable(ui->tableViewJuneExpenses, juneExpenseTableModel, true);
    configureTable(ui->tableViewJulyExpenses, julyExpenseTableModel, true);
    configureTable(ui->tableViewAugustExpenses, augustExpenseTableModel, true);
    configureTable(ui->tableViewSeptemberExpenses, septemberExpenseTableModel, true);
    configureTable(ui->tableViewOctoberExpenses, octoberExpenseTableModel, true);
    configureTable(ui->tableViewNovemberExpenses, novemberExpenseTableModel, true);
    configureTable(ui->tableViewDecemberExpenses, decemberExpenseTableModel, true);

    configureTable(ui->tableViewJanuaryInvestments, januaryInvestmentTableModel, false);
    configureTable(ui->tableViewFebruaryInvestments, februaryInvestmentTableModel, false);
    configureTable(ui->tableViewMarchInvestments, marchInvestmentTableModel, false);
    configureTable(ui->tableViewAprilInvestments, aprilInvestmentTableModel, false);
    configureTable(ui->tableViewMayInvestments, mayInvestmentTableModel, false);
    configureTable(ui->tableViewJuneInvestments, juneInvestmentTableModel, false);
    configureTable(ui->tableViewJulyInvestments, julyInvestmentTableModel, false);
    configureTable(ui->tableViewAugustInvestments, augustInvestmentTableModel, false);
    configureTable(ui->tableViewSeptemberInvestments, septemberInvestmentTableModel, false);
    configureTable(ui->tableViewOctoberInvestments, octoberInvestmentTableModel, false);
    configureTable(ui->tableViewNovemberInvestments, novemberInvestmentTableModel, false);
    configureTable(ui->tableViewDecemberInvestments, decemberInvestmentTableModel, false);
}

MonthlyBudgetSummaryDialog::~MonthlyBudgetSummaryDialog()
{
    delete ui;
}

void MonthlyBudgetSummaryDialog::onPushButtonExitClicked()
{
    close();
}

void MonthlyBudgetSummaryDialog::setTableData()
{
    januaryExpenseTableModel.setExpenseTypes();
    februaryExpenseTableModel.setExpenseTypes();
    marchExpenseTableModel.setExpenseTypes();
    aprilExpenseTableModel.setExpenseTypes();
    mayExpenseTableModel.setExpenseTypes();
    juneExpenseTableModel.setExpenseTypes();
    julyExpenseTableModel.setExpenseTypes();
    augustExpenseTableModel.setExpenseTypes();
    septemberExpenseTableModel.setExpenseTypes();
    octoberExpenseTableModel.setExpenseTypes();
    novemberExpenseTableModel.setExpenseTypes();
    decemberExpenseTableModel.setExpenseTypes();

    januaryInvestmentTableModel.setInvestmentTypes();
    februaryInvestmentTableModel.setInvestmentTypes();
    marchInvestmentTableModel.setInvestmentTypes();
    aprilInvestmentTableModel.setInvestmentTypes();
    mayInvestmentTableModel.setInvestmentTypes();
    juneInvestmentTableModel.setInvestmentTypes();
    julyInvestmentTableModel.setInvestmentTypes();
    augustInvestmentTableModel.setInvestmentTypes();
    septemberInvestmentTableModel.setInvestmentTypes();
    octoberInvestmentTableModel.setInvestmentTypes();
    novemberInvestmentTableModel.setInvestmentTypes();
    decemberInvestmentTableModel.setInvestmentTypes();
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
    tableView->setStyleSheet("QHeaderView::section { background-color: rgb(240, 240, 240) }");

    // Disable scroll bars
    tableView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    tableView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    // Disable cell resizing and selections
    tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed);
    tableView->horizontalHeader()->setFixedHeight(25);
    tableView->verticalHeader()->setSectionResizeMode(QHeaderView::Fixed);
    tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    tableView->setFocusPolicy(Qt::NoFocus);
    tableView->setSelectionMode(QAbstractItemView::NoSelection);

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
    tableView->resizeRowsToContents();
    if(isExpenseTable && (expenseTableHeight <= 0))
    {
        for(int i = 0; i < januaryExpenseTableModel.rowCount(); ++i)
        {
            expenseTableHeight += tableView->rowHeight(i);
        }

        expenseTableHeight += tableView->horizontalHeader()->height();
    }

    if(!isExpenseTable && (investmentTableHeight <= 0))
    {
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
