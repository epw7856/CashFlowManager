#include "ui_yearlybudgetsummarydialog.h"
#include "yearlybudgetsummarydialog.h"

YearlyBudgetSummaryDialog::YearlyBudgetSummaryDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::YearlyBudgetSummaryDialog)
{
    ui->setupUi(this);
}

YearlyBudgetSummaryDialog::~YearlyBudgetSummaryDialog()
{
    delete ui;
}
