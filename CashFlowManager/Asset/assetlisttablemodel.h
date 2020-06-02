#ifndef ASSETLISTTABLEMODEL_H
#define ASSETLISTTABLEMODEL_H

#include <QAbstractTableModel>
#include <QDate>
#include <vector>

class AssetInterface;
class AssetEntry;
class QVariant;

class AssetListTableModel : public QAbstractTableModel
{
public:
    AssetListTableModel(AssetInterface& localAssetInterface, int localYear);
    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    int columnCount(const QModelIndex& parent = QModelIndex()) const override;
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;
    void setAssetEntries();

    int getLiquidAssetTotalColumnIndex() const;
    int getLiquidAssetChangeColumnIndex() const;
    int getIlliquidAssetTotalColumnIndex() const;
    int getIlliquidAssetChangeColumnIndex() const;
    int getNetWorthTotalColumnIndex() const;
    int getNetWorthChangeColumnIndex() const;

private:
    void setTableData(int month);
    QString calculatePercentChange(double previousValue, double currentValue);
    AssetInterface& assetInterface;
    std::vector<AssetEntry*> liquidAssetEntries;
    std::vector<AssetEntry*> illiquidAssetEntries;
    int numRows = 0;
    int numCols = 0;
    int year = 0;
    std::vector<std::vector<QString>> tableData = {};
};

#endif // ASSETLISTTABLEMODEL_H
