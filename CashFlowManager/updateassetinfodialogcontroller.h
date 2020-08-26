#ifndef UPDATEASSETINFODIALOGCONTROLLER_H
#define UPDATEASSETINFODIALOGCONTROLLER_H

#include <QStringList>

class AssetInterface;

class UpdateAssetInfoDialogController
{
public:
    UpdateAssetInfoDialogController(AssetInterface& localAssetInterface);
    QStringList getAssetTypes() const;
    bool isAssetTypeLiquid(const QString& assetName) const;

private:
    AssetInterface& assetInterface;
};

#endif // UPDATEASSETINFODIALOGCONTROLLER_H
