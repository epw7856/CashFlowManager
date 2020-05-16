#include "expensetypesummarydialog.h"
#include "ui_expensetypesummarydialog.h"

ExpenseTypeSummaryDialog::ExpenseTypeSummaryDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ExpenseTypeSummaryDialog)
{
    ui->setupUi(this);
}

ExpenseTypeSummaryDialog::~ExpenseTypeSummaryDialog()
{
    delete ui;
}
