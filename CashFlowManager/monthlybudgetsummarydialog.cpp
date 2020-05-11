#include "monthlybudgetsummarydialog.h"
#include "ui_monthlybudgetsummarydialog.h"

MonthlyBudgetSummaryDialog::MonthlyBudgetSummaryDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MonthlyBudgetSummaryDialog)
{
    ui->setupUi(this);
}

MonthlyBudgetSummaryDialog::~MonthlyBudgetSummaryDialog()
{
    delete ui;
}
