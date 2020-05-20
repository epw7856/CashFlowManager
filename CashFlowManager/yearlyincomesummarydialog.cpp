#include <QScrollBar>
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
    salaryTableModel(localIncomeInterface, QDate::currentDate().year()),
    supplementalTableModel(localIncomeInterface, QDate::currentDate().year())
{
    ui->setupUi(this);
    setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);
    ui->labelDialogTitle->setText(QString("%1%2").arg(QString::number(QDate::currentDate().year())).arg(" Yearly Income Summary"));
    ui->verticalLayout_3->setAlignment(Qt::AlignTop);
    ui->verticalLayout_4->setAlignment(Qt::AlignTop);
    salaryTableModel.setSalaryIncomeTransactions();
    supplementalTableModel.setSupplementalIncomeTransactions();

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
    // Add table model data and disable selection
    ui->tableViewSalarySummary->setModel(&salaryTableModel);
    ui->tableViewSalarySummary->setSelectionMode(QAbstractItemView::NoSelection);

    // Set bold font for the header
    QFont font(ui->tableViewSalarySummary->font());
    font.setBold(true);
    ui->tableViewSalarySummary->horizontalHeader()->setFont(font);

    // Disable horizontal scroll bar
    ui->tableViewSalarySummary->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    // Disable cell resizing and selections
    ui->tableViewSalarySummary->horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed);
    ui->tableViewSalarySummary->horizontalHeader()->setFixedHeight(25);
    ui->tableViewSalarySummary->verticalHeader()->setSectionResizeMode(QHeaderView::Fixed);
    ui->tableViewSalarySummary->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableViewSalarySummary->setFocusPolicy(Qt::NoFocus);
    ui->tableViewSalarySummary->setSelectionMode(QAbstractItemView::NoSelection);

    // Add header frame
    //ui->tableViewExpenseSummary->horizontalHeader()->setFrameStyle(QFrame::HLine);
    //ui->tableViewExpenseSummary->horizontalHeader()->setFrameShadow(QFrame::Plain);
    //ui->tableViewExpenseSummary->horizontalHeader()->setLineWidth(1);

    // Resize columns to be uniform
    ui->tableViewSalarySummary->resizeColumnsToContents();

    // Set TableView height
    ui->tableViewSalarySummary->resizeRowsToContents();
    ui->tableViewSalarySummary->setMaximumHeight(ui->tableViewSalarySummary->rowHeight(0) * 24);

    // Set TableView width
    int tableWidth = 0;
    for(int i = 0; i < ui->tableViewSalarySummary->horizontalHeader()->count(); ++i)
    {
        tableWidth += ui->tableViewSalarySummary->horizontalHeader()->sectionSize(i);
    }

    if(ui->tableViewSalarySummary->verticalScrollBar()->width() < 100)
    {
        tableWidth += ui->tableViewSalarySummary->verticalScrollBar()->width();
    }

    ui->tableViewSalarySummary->setMinimumWidth(tableWidth);
    ui->tableViewSalarySummary->setMaximumWidth(tableWidth);
}

void YearlyIncomeSummaryDialog::configureSupplementalTable()
{
    // Add table model data and disable selection
    ui->tableViewSupplementalSummary->setModel(&supplementalTableModel);
    ui->tableViewSupplementalSummary->setSelectionMode(QAbstractItemView::NoSelection);

    // Set bold font for the header
    QFont font(ui->tableViewSupplementalSummary->font());
    font.setBold(true);
    ui->tableViewSupplementalSummary->horizontalHeader()->setFont(font);

    // Disable horizontal scroll bar
    ui->tableViewSupplementalSummary->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    // Disable cell resizing and selections
    ui->tableViewSupplementalSummary->horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed);
    ui->tableViewSupplementalSummary->horizontalHeader()->setFixedHeight(25);
    ui->tableViewSupplementalSummary->verticalHeader()->setSectionResizeMode(QHeaderView::Fixed);
    ui->tableViewSupplementalSummary->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableViewSupplementalSummary->setFocusPolicy(Qt::NoFocus);
    ui->tableViewSupplementalSummary->setSelectionMode(QAbstractItemView::NoSelection);

    // Add header frame
    //ui->tableViewExpenseSummary->horizontalHeader()->setFrameStyle(QFrame::HLine);
    //ui->tableViewExpenseSummary->horizontalHeader()->setFrameShadow(QFrame::Plain);
    //ui->tableViewExpenseSummary->horizontalHeader()->setLineWidth(1);

    // Resize columns to be uniform
    ui->tableViewSupplementalSummary->resizeColumnsToContents();

    // Set TableView height
    ui->tableViewSupplementalSummary->resizeRowsToContents();
    ui->tableViewSupplementalSummary->setMaximumHeight(ui->tableViewSupplementalSummary->rowHeight(0) * 24);

    // Set TableView width
    int tableWidth = 0;
    for(int i = 0; i < ui->tableViewSupplementalSummary->horizontalHeader()->count(); ++i)
    {
        tableWidth += ui->tableViewSupplementalSummary->horizontalHeader()->sectionSize(i);
    }

    if(ui->tableViewSupplementalSummary->verticalScrollBar()->width() < 100)
    {
        tableWidth += ui->tableViewSupplementalSummary->verticalScrollBar()->width();
    }

    ui->tableViewSupplementalSummary->setMinimumWidth(tableWidth);
    ui->tableViewSupplementalSummary->setMaximumWidth(tableWidth);
}
