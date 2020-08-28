#ifndef UPDATEASSETINFODIALOGCONTROLLER_H
#define UPDATEASSETINFODIALOGCONTROLLER_H

#include <QDate>
#include <QStringList>

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

private:
    AssetInterface& assetInterface;
    QDate date;
};

#endif // UPDATEASSETINFODIALOGCONTROLLER_H
