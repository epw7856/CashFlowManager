#include "assetinterface.h"
#include "assetsummarydialog.h"
#include <QScrollBar>
#include "ui_assetsummarydialog.h"

AssetSummaryDialog::AssetSummaryDialog(AssetInterface& localAssetInterface, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AssetSummaryDialog),
    assetListTable(localAssetInterface, QDate::currentDate().year())
{
    ui->setupUi(this);
    setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);
    ui->labelDialogTitle->setText(QString("%1%2").arg(QString::number(QDate::currentDate().year())).arg(" Asset and Net Worth Summary"));

    assetListTable.setAssetEntries();

    connect(ui->pushButtonExit, &QPushButton::clicked, this, &AssetSummaryDialog::onPushButtonExitClicked);

    configureAssetListTable();
}

AssetSummaryDialog::~AssetSummaryDialog()
{
    delete ui;
}

void AssetSummaryDialog::onPushButtonExitClicked()
{
    close();
}

void AssetSummaryDialog::configureAssetListTable()
{
    // Add table model data and disable selection
    ui->tableViewAssetSummary->setModel(&assetListTable);
    ui->tableViewAssetSummary->setSelectionMode(QAbstractItemView::NoSelection);

    // Set bold font for the header
    QFont font(ui->tableViewAssetSummary->font());
    font.setBold(true);
    ui->tableViewAssetSummary->horizontalHeader()->setFont(font);

    // Disable horizontal scroll bar
    ui->tableViewAssetSummary->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    // Disable cell resizing and selections
    ui->tableViewAssetSummary->horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed);
    ui->tableViewAssetSummary->horizontalHeader()->setFixedHeight(25);
    ui->tableViewAssetSummary->verticalHeader()->setSectionResizeMode(QHeaderView::Fixed);
    ui->tableViewAssetSummary->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableViewAssetSummary->setFocusPolicy(Qt::NoFocus);
    ui->tableViewAssetSummary->setSelectionMode(QAbstractItemView::NoSelection);

    // Add header frame
    //ui->tableViewExpenseSummary->horizontalHeader()->setFrameStyle(QFrame::HLine);
    //ui->tableViewExpenseSummary->horizontalHeader()->setFrameShadow(QFrame::Plain);
    //ui->tableViewExpenseSummary->horizontalHeader()->setLineWidth(1);

    // Resize columns to be uniform
    ui->tableViewAssetSummary->resizeColumnsToContents();
    int maxColumnWidth = 0;
    for(int i = 1; i < assetListTable.columnCount(); ++i)
    {
        int currentColumnWidth = ui->tableViewAssetSummary->columnWidth(i);
        if(currentColumnWidth > maxColumnWidth)
        {
            maxColumnWidth = currentColumnWidth;
        }
    }

    for(int i = 1; i < assetListTable.columnCount(); ++i)
    {
        ui->tableViewAssetSummary->setColumnWidth(i, maxColumnWidth);
    }

    // Set TableView height
    int tableHeight = 0;
    ui->tableViewAssetSummary->resizeRowsToContents();
    for(int i = 0; i < assetListTable.rowCount(); ++i)
    {
        tableHeight += ui->tableViewAssetSummary->rowHeight(i);
    }

    tableHeight += ui->tableViewAssetSummary->horizontalHeader()->height();
    //ui->tableViewAssetSummary->setMinimumHeight(tableHeight+5);
    //ui->tableViewAssetSummary->setMaximumHeight(tableHeight+5);
    ui->tableViewAssetSummary->setFixedHeight(tableHeight+5);

    // Set TableView width
    int tableWidth = 0;
    for(int i = 0; i < ui->tableViewAssetSummary->horizontalHeader()->count(); ++i)
    {
        tableWidth += ui->tableViewAssetSummary->horizontalHeader()->sectionSize(i);
    }

    if(ui->tableViewAssetSummary->verticalScrollBar()->width() < 100)
    {
        tableWidth += ui->tableViewAssetSummary->verticalScrollBar()->width();
    }

    //ui->tableViewAssetSummary->setMaximumWidth(tableWidth);
    //ui->tableViewAssetSummary->setMinimumWidth(tableWidth);
    ui->tableViewAssetSummary->setFixedWidth(tableWidth);
}
