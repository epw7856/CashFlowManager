#include "assetentry.h"
#include "assetinterface.h"
#include "assetlisttablemodel.h"
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
    std::pair<QDate, QDate> dates = DateUtilities::getYearlyDates(year);
    startDatePeriod = dates.first;
    endDatePeriod = dates.second;
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
        int numRows = rowCount(index);

        if((index.row() < numRows))
        {
            auto rowUint = static_cast<quint32>(index.row());
            auto colUint = static_cast<quint32>(index.column());

            if(rowUint == 0)
            {
                if(colUint == 0)
                {
                    return "January";
                }
//                else if(colUint > 0 && colUint < (numLiquidAssets + 1))
//                {

//                }
            }
            else if(rowUint == 1 && index.column() == 0)
            {
                return "February";
            }
            else if(rowUint == 2 && index.column() == 0)
            {
                return "March";
            }
            else if(rowUint == 3 && index.column() == 0)
            {
                return "April";
            }
            else if(rowUint == 4 && index.column() == 0)
            {
                return "May";
            }
            else if(rowUint == 5 && index.column() == 0)
            {
                return "June";
            }
            else if(rowUint == 6 && index.column() == 0)
            {
                return "July";
            }
            else if(rowUint == 7 && index.column() == 0)
            {
                return "August";
            }
            else if(rowUint == 8 && index.column() == 0)
            {
                return "September";
            }
            else if(rowUint == 9 && index.column() == 0)
            {
                return "October";
            }
            else if(rowUint == 10 && index.column() == 0)
            {
                return "November";
            }
            else if(rowUint == 11 && index.column() == 0)
            {
                return "December";
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

    if((role == Qt::FontRole) && (index.column() == 0))
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

            for(int i = 1; i < static_cast<int>(liquidAssetEntries.size() + 1); ++i)
            {
                if(section == i)
                {
                    return QString::fromStdString(liquidAssetEntries[i-1]->getName());
                }
            }

            if(section == static_cast<int>(liquidAssetEntries.size() + 1))
            {
                return "Liquid Asset Total ";
            }
            else if(section == static_cast<int>(liquidAssetEntries.size() + 2))
            {
                return "% Change";
            }

            for(int i = static_cast<int>(liquidAssetEntries.size() + 3); i < static_cast<int>(illiquidAssetEntries.size() + liquidAssetEntries.size() + 3); ++i)
            {
                if(section == i)
                {
                    return QString::fromStdString(illiquidAssetEntries[i - static_cast<int>(liquidAssetEntries.size() + 3)]->getName());
                }
            }

            if(section == static_cast<int>(liquidAssetEntries.size() + 3 + illiquidAssetEntries.size()))
            {
                return "Illiquid Asset Total ";
            }
            else if(section == static_cast<int>(liquidAssetEntries.size() + 3 + illiquidAssetEntries.size() + 1))
            {
                return "% Change";
            }
            else if(section == static_cast<int>(liquidAssetEntries.size() + 3 + illiquidAssetEntries.size() + 2))
            {
                return "Net Worth";
            }
            else if(section == static_cast<int>(liquidAssetEntries.size() + 3 + illiquidAssetEntries.size() + 3))
            {
                return "% Change";
            }



//            if(section == 0)
//            {
//                return "";
//            }
//            else if(section == 1)
//            {
//                return "January";
//            }
//            else if(section == 2)
//            {
//                return "February";
//            }
//            else if(section == 3)
//            {
//                return "March";
//            }
//            else if(section == 4)
//            {
//                return "April";
//            }
//            else if(section == 5)
//            {
//                return "May";
//            }
//            else if(section == 6)
//            {
//                return "June";
//            }
//            else if(section == 7)
//            {
//                return "July";
//            }
//            else if(section == 8)
//            {
//                return "August";
//            }
//            else if(section == 9)
//            {
//                return "September";
//            }
//            else if(section == 10)
//            {
//                return "October";
//            }
//            else if(section == 11)
//            {
//                return "November";
//            }
//            else if(section == 12)
//            {
//                return "December";
//            }
        }
    }

    return {};
}

void AssetListTableModel::setAssetEntries()
{
    liquidAssetEntries = assetInterface.getAssetListByType(AssetType::Liquid);
    illiquidAssetEntries = assetInterface.getAssetListByType(AssetType::Illiquid);

    numLiquidAssets = liquidAssetEntries.size();
    numIlliquidAssets = illiquidAssetEntries.size();

    numCols = static_cast<int>(liquidAssetEntries.size() + illiquidAssetEntries.size() + 6);
}
