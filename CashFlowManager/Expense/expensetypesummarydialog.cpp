#include "expenseinterface.h"
#include "expensetypesummarydialog.h"
#include <QScrollBar>
#include "ui_expensetypesummarydialog.h"

ExpenseTypeSummaryDialog::ExpenseTypeSummaryDialog(ExpenseInterface& localExpenseInterface, QWidget* parent)
:
    QDialog(parent),
    ui(new Ui::ExpenseTypeSummaryDialog),
    januaryExpenseTable(localExpenseInterface, 1),
    februaryExpenseTable(localExpenseInterface, 2),
    marchExpenseTable(localExpenseInterface, 3),
    aprilExpenseTable(localExpenseInterface, 4),
    mayExpenseTable(localExpenseInterface, 5),
    juneExpenseTable(localExpenseInterface, 6),
    julyExpenseTable(localExpenseInterface, 7),
    augustExpenseTable(localExpenseInterface, 8),
    septemberExpenseTable(localExpenseInterface, 9),
    octoberExpenseTable(localExpenseInterface, 10),
    novemberExpenseTable(localExpenseInterface, 11),
    decemberExpenseTable(localExpenseInterface, 12)
{
    ui->setupUi(this);
    setWindowTitle("");
    ui->labelDialogTitle->setText("");
    showMaximized();
    setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);
    setWindowFlag(Qt::WindowMinMaxButtonsHint);

    connect(ui->pushButtonExit, &QPushButton::clicked, this, &ExpenseTypeSummaryDialog::onPushButtonExitClicked);
}

ExpenseTypeSummaryDialog::~ExpenseTypeSummaryDialog()
{
    delete ui;
}

void ExpenseTypeSummaryDialog::onPushButtonExitClicked()
{
    close();
}

void ExpenseTypeSummaryDialog::updateExpenseType(std::string type)
{
    setWindowTitle(QString("%1").arg(QString::fromStdString(type) + " Expense Summary"));
    ui->labelDialogTitle->setText(QString::number(QDate::currentDate().year()) + " " + QString::fromStdString(type) + " Expense Summary");

    setTableData(type);
    configureAllTables();
}

void ExpenseTypeSummaryDialog::configureAllTables()
{
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

void ExpenseTypeSummaryDialog::setTableData(std::string type)
{
    januaryExpenseTable.setExpenseTransactions(type);
    februaryExpenseTable.setExpenseTransactions(type);
    marchExpenseTable.setExpenseTransactions(type);
    aprilExpenseTable.setExpenseTransactions(type);
    mayExpenseTable.setExpenseTransactions(type);
    juneExpenseTable.setExpenseTransactions(type);
    julyExpenseTable.setExpenseTransactions(type);
    augustExpenseTable.setExpenseTransactions(type);
    septemberExpenseTable.setExpenseTransactions(type);
    octoberExpenseTable.setExpenseTransactions(type);
    novemberExpenseTable.setExpenseTransactions(type);
    decemberExpenseTable.setExpenseTransactions(type);
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
    tableView->resizeColumnsToContents();

    // Set TableView height
    tableView->resizeRowsToContents();

    int tableHeight = 0;
    for(int i = 0; i < tableModel.rowCount(); ++i)
    {
        tableHeight += tableView->rowHeight(i);
    }

    tableHeight += tableView->horizontalHeader()->height();
    tableView->setFixedHeight(tableHeight);

    // Set TableView width
    int tableWidth = 0;
    for(int i = 0; i < tableView->horizontalHeader()->count(); ++i)
    {
        tableWidth += tableView->horizontalHeader()->sectionSize(i);
    }

    tableView->setMinimumWidth(tableWidth);
    tableView->setMaximumWidth(tableWidth);
}
