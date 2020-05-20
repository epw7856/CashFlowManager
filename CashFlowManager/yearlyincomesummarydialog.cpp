#include "yearlyincomesummarydialog.h"
#include "ui_yearlyincomesummarydialog.h"

YearlyIncomeSummaryDialog::YearlyIncomeSummaryDialog
(
    IncomeInterface& localIncomeInterface,
    QWidget* parent
)
:
    QDialog(parent),
    ui(new Ui::YearlyIncomeSummaryDialog),
    salaryTable(localIncomeInterface, QDate::currentDate().year()),
    supplementalTable(localIncomeInterface, QDate::currentDate().year())
{
    ui->setupUi(this);
    setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);
    ui->labelDialogTitle->setText(QString("%1%2").arg(QString::number(QDate::currentDate().year())).arg(" Yearly Income Summary"));
    ui->verticalLayout_3->setAlignment(Qt::AlignTop);
    ui->verticalLayout_4->setAlignment(Qt::AlignTop);
    salaryTable.setSalaryIncomeTransactions();
    supplementalTable.setSupplementalIncomeTransactions();

    connect(ui->pushButtonExit, &QPushButton::clicked, this, &YearlyIncomeSummaryDialog::onPushButtonExitClicked);

    configureSalaryTable();
    configureSupplementalTable();
}

YearlyIncomeSummaryDialog::~YearlyIncomeSummaryDialog()
{
    delete ui;
}

void YearlyIncomeSummaryDialog::onPushButtonExitClicked()
{
    close();
}

void YearlyIncomeSummaryDialog::configureSalaryTable()
{

}

void YearlyIncomeSummaryDialog::configureSupplementalTable()
{

}
