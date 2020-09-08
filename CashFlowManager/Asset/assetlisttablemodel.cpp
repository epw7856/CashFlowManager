#include "assetentry.h"
#include "assetinterface.h"
#include "assetlisttablemodel.h"
#include "currencyutilities.h"
#include "dateutilities.h"
#include <QBrush>
#include <QColor>
#include <QFont>

AssetListTableModel::AssetListTableModel(AssetInterface& localAssetInterface, int localYear)
:
    assetInterface(localAssetInterface),
    numRows(12),
    year(localYear)
{
    tableData.resize(12);
}

int AssetListTableModel::rowCount(const QModelIndex&) const
{
    return numRows;
}

int AssetListTableModel::columnCount(const QModelIndex&) const
{
    return numCols;
}

QVariant AssetListTableModel::data(const QModelIndex& index, int role) const
{
    if(role == Qt::DisplayRole)
    {
        if((index.row() < numRows) && (index.column() < numCols))
        {
            auto rowUint = static_cast<quint32>(index.row());
            auto colUint = static_cast<quint32>(index.column());

            if(colUint == 0)
            {
                if(rowUint == 0)
                {
                    return "January";
                }
                else if(rowUint == 1)
                {
                    return "February";
                }
                else if(rowUint == 2)
                {
                    return "March";
                }
                else if(rowUint == 3)
                {
                    return "April";
                }
                else if(rowUint == 4)
                {
                    return "May";
                }
                else if(rowUint == 5)
                {
                    return "June";
                }
                else if(rowUint == 6)
                {
                    return "July";
                }
                else if(rowUint == 7)
                {
                    return "August";
                }
                else if(rowUint == 8)
                {
                    return "September";
                }
                else if(rowUint == 9)
                {
                    return "October";
                }
                else if(rowUint == 10)
                {
                    return "November";
                }
                else if(rowUint == 11)
                {
                    return "December";
                }
            }

            if(colUint > 0)
            {
                if((QDate::currentDate().month() - 1) >= static_cast<int>(rowUint))
                {
                    if(static_cast<int>(rowUint) == (QDate::currentDate().month() - 1) &&
                       !assetInterface.currentMonthValuesEnteredForAllAssets())
                    {
                        return "";
                    }
                    else
                    {
                        return tableData[rowUint][colUint - 1];
                    }
                }
                else
                {
                    return "";
                }
            }
        }
    }

    if(role == Qt::BackgroundRole)
    {
        int stopIndex;
        (assetInterface.currentMonthValuesEnteredForAllAssets()) ? stopIndex = QDate::currentDate().month() : stopIndex = QDate::currentDate().month() - 1;

        if(index.row() < stopIndex)
        {
            if(index.column() == getLiquidAssetChangeColumnIndex())
            {
                if(index.sibling(index.row(), getLiquidAssetChangeColumnIndex()).data().toString() == "N/A")
                {
                    return {};
                }

                double liquidPercentage = CurrencyUtilities::formatRatioToDouble(index.sibling(index.row(), getLiquidAssetChangeColumnIndex()).data().toString().toStdString());
                if(liquidPercentage > 0.0)
                {
                    return QVariant(QBrush(QColor(Qt::darkGreen)));
                }
                else
                {
                    return QVariant(QBrush(QColor(Qt::red)));
                }
            }
            else if(index.column() == getIlliquidAssetChangeColumnIndex())
            {
                if(index.sibling(index.row(), getIlliquidAssetChangeColumnIndex()).data().toString() == "N/A")
                {
                    return {};
                }

                double illiquidPercentage = CurrencyUtilities::formatRatioToDouble(index.sibling(index.row(), getIlliquidAssetChangeColumnIndex()).data().toString().toStdString());
                if(illiquidPercentage > 0.0)
                {
                    return QVariant(QBrush(QColor(Qt::darkGreen)));
                }
                else
                {
                    return QVariant(QBrush(QColor(Qt::red)));
                }
            }
            else if(index.column() == getNetWorthChangeColumnIndex())
            {
                if(index.sibling(index.row(), getNetWorthChangeColumnIndex()).data().toString() == "N/A")
                {
                    return {};
                }

                double netWorthPercentage = CurrencyUtilities::formatRatioToDouble(index.sibling(index.row(), getNetWorthChangeColumnIndex()).data().toString().toStdString());
                if(netWorthPercentage > 0.0)
                {
                    return QVariant(QBrush(QColor(Qt::darkGreen)));
                }
                else
                {
                    return QVariant(QBrush(QColor(Qt::red)));
                }
            }
        }
    }

    if(role == Qt::TextAlignmentRole)
    {
        int numRows = rowCount(index);
        if((index.row() < numRows) && (index.column() < numCols))
        {
            if(index.column()!= 0)
            {
                return Qt::AlignCenter;
            }
        }
    }

    if((role == Qt::FontRole) &&
      ((index.column() == 0) ||
       (index.column() == getLiquidAssetTotalColumnIndex()) ||
       (index.column() == getIlliquidAssetTotalColumnIndex()) ||
       (index.column() == getNetWorthTotalColumnIndex())))
    {
        QFont font;
        font.setBold(true);
        return font;
    }

    return {};
}

QVariant AssetListTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if(role == Qt::DisplayRole)
    {
        if(orientation == Qt::Horizontal)
        {
            if(section == 0)
            {
                return "";
            }
            else if(section < getLiquidAssetTotalColumnIndex())
            {
                return QString::fromStdString(liquidAssetEntries[section - 1]->getName());
            }
            else if(section == getLiquidAssetTotalColumnIndex())
            {
                return "Liquid Total";
            }
            else if(section == getLiquidAssetChangeColumnIndex())
            {
                return "% Change";
            }
            else if(section < getIlliquidAssetTotalColumnIndex())
            {
                return QString::fromStdString(illiquidAssetEntries[section - getLiquidAssetChangeColumnIndex() - 1]->getName());
            }
            else if(section == getIlliquidAssetTotalColumnIndex())
            {
                return "Illiquid Total";
            }
            else if(section == getIlliquidAssetChangeColumnIndex())
            {
                return "% Change";
            }
            else if(section == getNetWorthTotalColumnIndex())
            {
                return "Net Worth";
            }
            else if(section == getNetWorthChangeColumnIndex())
            {
                return "% Change";
            }
        }
    }

    if((role == Qt::FontRole) && ((section < getLiquidAssetTotalColumnIndex()) || (section < getIlliquidAssetTotalColumnIndex())))
    {
        if((section < getLiquidAssetTotalColumnIndex()) ||
           ((section > getLiquidAssetChangeColumnIndex()) && (section < getIlliquidAssetTotalColumnIndex())))
        {
            QFont font;
            font.setBold(false);
            return font;
        }
    }

    return {};
}

void AssetListTableModel::setAssetEntries()
{
    liquidAssetEntries = assetInterface.getAssetListByType(AssetType::Liquid);
    illiquidAssetEntries = assetInterface.getAssetListByType(AssetType::Illiquid);

    numCols = static_cast<int>(liquidAssetEntries.size() + illiquidAssetEntries.size() + 7);

    for(int i = 1; i <= QDate::currentDate().month(); ++i)
    {
        if(i == QDate::currentDate().month() && !assetInterface.currentMonthValuesEnteredForAllAssets())
        {
            break;
        }
        else
        {
            setTableData(i);
        }
    }
}

void AssetListTableModel::setTableData(int month)
{
    QDate date(year, month, 1);
    QDate prevDate = date.addMonths(-1);
    double currentLiquidValue = assetInterface.getAssetTotalValueByType(AssetType::Liquid, year, month);
    double previousLiquidValue = assetInterface.getAssetTotalValueByType(AssetType::Liquid, prevDate.year(), prevDate.month());
    double currentIlliquidValue = assetInterface.getAssetTotalValueByType(AssetType::Illiquid, year, month);
    double previousIlliquidValue = assetInterface.getAssetTotalValueByType(AssetType::Illiquid, prevDate.year(), prevDate.month());

    for(const auto& i : liquidAssetEntries)
    {
        tableData[month - 1].push_back(QString::fromStdString(CurrencyUtilities::formatCurrency(assetInterface.getAssetValue(i->getName(), year, month))));
    }

    tableData[month - 1].push_back(QString::fromStdString(CurrencyUtilities::formatCurrency(currentLiquidValue)));
    tableData[month - 1].push_back(calculatePercentChange(previousLiquidValue, currentLiquidValue));

    for(const auto& i : illiquidAssetEntries)
    {
        tableData[month - 1].push_back(QString::fromStdString(CurrencyUtilities::formatCurrency(assetInterface.getAssetValue(i->getName(), year, month))));
    }

    tableData[month - 1].push_back(QString::fromStdString(CurrencyUtilities::formatCurrency(currentIlliquidValue)));
    tableData[month - 1].push_back(calculatePercentChange(previousIlliquidValue, currentIlliquidValue));

    tableData[month - 1].push_back(QString::fromStdString(CurrencyUtilities::formatCurrency(currentLiquidValue + currentIlliquidValue)));
    tableData[month - 1].push_back(calculatePercentChange((previousLiquidValue + previousIlliquidValue), (currentLiquidValue + currentIlliquidValue)));
}

QString AssetListTableModel::calculatePercentChange(double previousValue, double currentValue)
{
    return (previousValue > 0.0) ? QString::fromStdString(CurrencyUtilities::formatRatio((currentValue - previousValue) / previousValue))
                                 : "N/A";
}

int AssetListTableModel::getLiquidAssetTotalColumnIndex() const
{
    return liquidAssetEntries.size() + 1;
}

int AssetListTableModel::getLiquidAssetChangeColumnIndex() const
{
    return (liquidAssetEntries.size() + 2);
}

int AssetListTableModel::getIlliquidAssetTotalColumnIndex() const
{
    return (liquidAssetEntries.size() + illiquidAssetEntries.size() + 3);
}

int AssetListTableModel::getIlliquidAssetChangeColumnIndex() const
{
    return (liquidAssetEntries.size() + illiquidAssetEntries.size() + 4);
}

int AssetListTableModel::getNetWorthTotalColumnIndex() const
{
    return (liquidAssetEntries.size() + illiquidAssetEntries.size() + 5);
}

int AssetListTableModel::getNetWorthChangeColumnIndex() const
{
    return (liquidAssetEntries.size() + illiquidAssetEntries.size() + 6);
}
