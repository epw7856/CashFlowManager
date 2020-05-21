#include "assetinterface.h"
#include "assetlisttablemodel.h"
#include "dateutilities.h"

AssetListTableModel::AssetListTableModel(AssetInterface& localAssetInterface, AssetType localType, int localYear)
:
    assetInterface(localAssetInterface),
    numCols(13),
    type(localType),
    year(localYear)
{
    std::pair<QDate, QDate> dates = DateUtilities::getYearlyDates(year);
    startDatePeriod = dates.first;
    endDatePeriod = dates.second;
}

int AssetListTableModel::rowCount(const QModelIndex&) const
{
    return static_cast<int>(assetEntries.size()) + 2;
}

int AssetListTableModel::columnCount(const QModelIndex&) const
{
    return numCols;
}

QVariant AssetListTableModel::data(const QModelIndex& index, int role) const
{

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
            else if(section == 1)
            {
                return "January";
            }
            else if(section == 2)
            {
                return "February";
            }
            else if(section == 3)
            {
                return "March";
            }
            else if(section == 4)
            {
                return "April";
            }
            else if(section == 5)
            {
                return "May";
            }
            else if(section == 6)
            {
                return "June";
            }
            else if(section == 7)
            {
                return "July";
            }
            else if(section == 8)
            {
                return "August";
            }
            else if(section == 9)
            {
                return "September";
            }
            else if(section == 10)
            {
                return "October";
            }
            else if(section == 11)
            {
                return "November";
            }
            else if(section == 12)
            {
                return "December";
            }
        }
    }

    return {};
}

void AssetListTableModel::setAssetEntries()
{
    assetEntries = assetInterface.getAssetListByType(type);
}
