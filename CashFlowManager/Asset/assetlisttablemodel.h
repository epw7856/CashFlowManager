#ifndef ASSETLISTTABLEMODEL_H
#define ASSETLISTTABLEMODEL_H

#include "assettype.h"
#include <QAbstractTableModel>
#include <QDate>
#include <vector>

class AssetInterface;
class AssetEntry;
class QVariant;

class AssetListTableModel : public QAbstractTableModel
{
public:
    AssetListTableModel(AssetInterface& localAssetInterface, AssetType localType, int localYear);
    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    int columnCount(const QModelIndex& parent = QModelIndex()) const override;
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;
    void setAssetEntries();

private:
    AssetInterface& assetInterface;
    std::vector<AssetEntry*> assetEntries;
    int numCols = 0;
    QDate startDatePeriod;
    QDate endDatePeriod;
    AssetType type = AssetType::Unknown;
    int year = 0;
};

#endif // ASSETLISTTABLEMODEL_H
