#include "assetentry.h"
#include "assetinterface.h"
#include "updateassetinfodialogcontroller.h"

UpdateAssetInfoDialogController::UpdateAssetInfoDialogController(AssetInterface& localAssetInterface)
:
    assetInterface(localAssetInterface)
{

}

QStringList UpdateAssetInfoDialogController::getAssetTypes() const
{
    QStringList assetList;

    for(auto& asset : assetInterface.getAssetList())
    {
        assetList.push_back(QString::fromStdString(asset->getName()));
    }

    return assetList;
}
