#include "assetinterface.h"
#include "assetsummarydialog.h"
#include "assetsummarydialogcontroller.h"
#include "currencyutilities.h"
#include <QScrollBar>
#include "ui_assetsummarydialog.h"

AssetSummaryDialog::AssetSummaryDialog(AssetInterface& localAssetInterface, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AssetSummaryDialog),
    assetListTable(localAssetInterface, QDate::currentDate().year()),
    controller(std::make_unique<AssetSummaryDialogController>(localAssetInterface))
{
    ui->setupUi(this);
    setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);
    setWindowFlag(Qt::WindowMinMaxButtonsHint);
    ui->labelDialogTitle->setText(QString("%1%2").arg(QString::number(QDate::currentDate().year())).arg(" Asset and Net Worth Summary"));
    ui->labelYearlyNetWorthTracker->setText("Net Worth Tracking");
    ui->labelLiquidAssetAmount->setText(QString::fromStdString(controller->getCurrentLiquidAssetAmount()));
    ui->labelLiquidAssetPercent->setText(QString::fromStdString(controller->getYearlyChange(false, AssetType::Liquid)));
    ui->labelIlliquidAssetAmount->setText(QString::fromStdString(controller->getCurrentIlliquidAssetAmount()));
    ui->labelIlliquidAssetPercent->setText(QString::fromStdString(controller->getYearlyChange(false, AssetType::Illiquid)));
    ui->labelNetWorthAmount->setText(QString::fromStdString(controller->getCurrentNetWorthAmount()));
    ui->labelNetWorthPercent->setText(QString::fromStdString(controller->getYearlyChange(true)));

    assetListTable.setAssetEntries();

    connect(ui->pushButtonExit, &QPushButton::clicked, this, &AssetSummaryDialog::onPushButtonExitClicked);

    configureAssetListTable();
    configureNetWorthTrackingChart();
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

    // Set scrollbar policies
    ui->tableViewAssetSummary->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->tableViewAssetSummary->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);

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

    if(ui->tableViewAssetSummary->horizontalScrollBar()->height() < 100)
    {
        tableHeight += ui->tableViewAssetSummary->horizontalScrollBar()->height();
    }

    ui->tableViewAssetSummary->setMinimumHeight(tableHeight - 100);
    ui->tableViewAssetSummary->setMaximumHeight(tableHeight);

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

    ui->tableViewAssetSummary->setMinimumWidth(tableWidth);
    ui->tableViewAssetSummary->setMaximumWidth(tableWidth);
}

void AssetSummaryDialog::configureNetWorthTrackingChart()
{
    QLineSeries* series = new QLineSeries();

    std::pair<double, double> range = controller->getPastYearMinandMaxNetWorth();
    double tickCount = 5.0;
    std::vector<double> values = controller->getPastYearNetWorthTotals();
    std::reverse(values.begin(), values.end());
    for(quint32 i = 0; i < values.size(); ++i)
    {
        series->append(i, values[i]);
    }

    QChart* chart = new QChart();
    chart->legend()->hide();
    chart->addSeries(series);
    chart->createDefaultAxes();

    auto axisX = (chart->axes(Qt::Horizontal)).at(0);
    auto axisY = (chart->axes(Qt::Vertical)).at(0);
    axisX->setVisible(false);
    axisY->setVisible(false);

    QCategoryAxis* labelX = new QCategoryAxis;
    QCategoryAxis* labelY = new QCategoryAxis;
    labelX->setLabelsPosition(QCategoryAxis::AxisLabelsPositionOnValue);
    labelY->setLabelsPosition(QCategoryAxis::AxisLabelsPositionOnValue);

    int index = 12;
    QDate date(QDate::currentDate());
    if(!controller->getCurrentMonthValuesEntered())
    {
        date = date.addMonths(-1);
    }

    date = date.addMonths(-11);
    for(int i = 0; i < index; ++i)
    {
        labelX->append(date.toString("MMM yy"), i);
        date = date.addMonths(1);
    }
    labelX->setRange(0, index - 1);
    axisX->setRange(0, index - 1);

    double min = range.first * .9;
    double max = range.second * 1.1;
    double increment = (max - min) / tickCount;

    for(int i = 0; i < tickCount; ++i)
    {
        int value = std::floor(min + (i * increment));
        labelY->append(QString::fromStdString(CurrencyUtilities::formatCurrency(value, true)), value);
    }
    labelY->setRange(min, min + (tickCount * increment));
    axisY->setRange(min, min + (tickCount * increment));

    chart->addAxis(labelX, Qt::AlignBottom);
    chart->addAxis(labelY, Qt::AlignLeft);

    ui->graphicsViewNetWorth->setChart(chart);
}
