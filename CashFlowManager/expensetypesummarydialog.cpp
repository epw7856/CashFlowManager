#include "expenseinterface.h"
#include "expensetypesummarydialog.h"
#include <QScrollBar>
#include "ui_expensetypesummarydialog.h"

ExpenseTypeSummaryDialog::ExpenseTypeSummaryDialog
(
    ExpenseInterface& localExpenseInterface,
    std::string localExpenseType,
    QWidget* parent
)
:
    QDialog(parent),
    ui(new Ui::ExpenseTypeSummaryDialog),
    expenseType(localExpenseType),
    januaryExpenseTable(localExpenseInterface, expenseType, 1),
    februaryExpenseTable(localExpenseInterface, expenseType, 2),
    marchExpenseTable(localExpenseInterface, expenseType, 3),
    aprilExpenseTable(localExpenseInterface, expenseType, 4),
    mayExpenseTable(localExpenseInterface, expenseType, 5),
    juneExpenseTable(localExpenseInterface, expenseType, 6),
    julyExpenseTable(localExpenseInterface, expenseType, 7),
    augustExpenseTable(localExpenseInterface, expenseType, 8),
    septemberExpenseTable(localExpenseInterface, expenseType, 9),
    octoberExpenseTable(localExpenseInterface, expenseType, 10),
    novemberExpenseTable(localExpenseInterface, expenseType, 11),
    decemberExpenseTable(localExpenseInterface, expenseType, 12)
{
    ui->setupUi(this);
    setWindowTitle(QString("%1").arg(QString::fromStdString(expenseType) + " Expense Summary"));
    ui->labelDialogTitle->setText(QString::number(QDate::currentDate().year()) + " " + QString::fromStdString(expenseType) + " Expense Summary");
    showMaximized();
    ui->verticalLayout_3->setAlignment(Qt::AlignTop);
    setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);
    setWindowFlag(Qt::WindowMinMaxButtonsHint);

    setTableData();

    configureExpenseTable(ui->tableViewJanuaryExpenses, januaryExpenseTable);
    configureExpenseTable(ui->tableViewFebruaryExpenses, februaryExpenseTable);
    configureExpenseTable(ui->tableViewMarchExpenses, marchExpenseTable);
    configureExpenseTable(ui->tableViewAprilExpenses, aprilExpenseTable);
    configureExpenseTable(ui->tableViewMayExpenses, mayExpenseTable);
    configureExpenseTable(ui->tableViewJuneExpenses, juneExpenseTable);
    configureExpenseTable(ui->tableViewJulyExpenses, julyExpenseTable);
    configureExpenseTable(ui->tableViewAugustExpenses, augustExpenseTable);
    configureExpenseTable(ui->tableViewSeptemberExpenses, septemberExpenseTable);
    configureExpenseTable(ui->tableViewOctoberExpenses, octoberExpenseTable);
    configureExpenseTable(ui->tableViewNovemberExpenses, novemberExpenseTable);
    configureExpenseTable(ui->tableViewDecemberExpenses, decemberExpenseTable);
}

ExpenseTypeSummaryDialog::~ExpenseTypeSummaryDialog()
{
    delete ui;
}

void ExpenseTypeSummaryDialog::setTableData()
{
    januaryExpenseTable.setExpenseTransactions();
    februaryExpenseTable.setExpenseTransactions();
    marchExpenseTable.setExpenseTransactions();
    aprilExpenseTable.setExpenseTransactions();
    mayExpenseTable.setExpenseTransactions();
    juneExpenseTable.setExpenseTransactions();
    julyExpenseTable.setExpenseTransactions();
    augustExpenseTable.setExpenseTransactions();
    septemberExpenseTable.setExpenseTransactions();
    octoberExpenseTable.setExpenseTransactions();
    novemberExpenseTable.setExpenseTransactions();
    decemberExpenseTable.setExpenseTransactions();
}

void ExpenseTypeSummaryDialog::configureExpenseTable(QTableView* tableView, QAbstractTableModel& tableModel)
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
    tableView->resizeColumnsToContents();
//    int maxColumnWidth = 0;
//    for(int i = 0; i < tableModel.columnCount(); ++i)
//    {
//        tableView->resizeColumnToContents(i);
//        int currentColumnWidth = tableView->columnWidth(i);
//        if(currentColumnWidth > maxColumnWidth)
//        {
//            maxColumnWidth = currentColumnWidth;
//        }
//    }

//    tableView->setColumnWidth(1, maxColumnWidth);
//    tableView->setColumnWidth(2, maxColumnWidth);
//    tableView->setColumnWidth(3, maxColumnWidth);

    // Set TableView height
//    int tableHeight = 0;
    tableView->resizeRowsToContents();
//    for(int i = 0; i < tableModel.rowCount(); ++i)
//    {
//        tableHeight += tableView->rowHeight(i);
//    }

//    tableHeight += tableView->horizontalHeader()->height();
    tableView->setMaximumHeight(tableView->rowHeight(0) * 12);

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
