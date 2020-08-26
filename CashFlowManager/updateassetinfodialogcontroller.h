#ifndef UPDATEASSETINFODIALOGCONTROLLER_H
#define UPDATEASSETINFODIALOGCONTROLLER_H

#include <QStringList>

class AssetInterface;

class UpdateAssetInfoDialogController
{
public:
    UpdateAssetInfoDialogController(AssetInterface& localAssetInterface);
    QStringList getAssetTypes() const;

private:
    AssetInterface& assetInterface;
};

#endif // UPDATEASSETINFODIALOGCONTROLLER_H
