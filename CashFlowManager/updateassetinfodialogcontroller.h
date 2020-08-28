#ifndef UPDATEASSETINFODIALOGCONTROLLER_H
#define UPDATEASSETINFODIALOGCONTROLLER_H

#include "assettype.h"
#include <QDate>
#include <QStringList>
#include <vector>

class AssetInterface;

class UpdateAssetInfoDialogController
{
public:
    UpdateAssetInfoDialogController(AssetInterface& localAssetInterface);
    QString getMonthString(int previousMonth) const;
    QString getAssetValue(const QString& assetName, int previousMonth) const;
    QStringList getAssetTypes() const;
    bool isAssetTypeLiquid(const QString& assetName) const;
    void deleteAsset(const QString& assetName);
    bool verifyAssetValue(QString value) const;
    bool verifyAssetName(const QString& assetName) const;
    void updateAsset(const QString& currentAssetName,
                     const QString& updatedAssetName,
                     AssetType type,
                     std::vector<QString>& values);

private:
    AssetInterface& assetInterface;
    QDate date;
};

#endif // UPDATEASSETINFODIALOGCONTROLLER_H
