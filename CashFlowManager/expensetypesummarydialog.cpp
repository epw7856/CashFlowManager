#include "expenseinterface.h"
#include "expensetypesummarydialog.h"
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

void ExpenseTypeSummaryDialog::configureExpenseTable(QTableView* tableView, QAbstractTableModel& tableModel)
{

}
