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
    expenseInterface(localExpenseInterface),
    expenseType(localExpenseType)
{
    ui->setupUi(this);
}

ExpenseTypeSummaryDialog::~ExpenseTypeSummaryDialog()
{
    delete ui;
}
