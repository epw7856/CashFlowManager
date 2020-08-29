#ifndef UPDATECURRENTASSETVALUESDIALOGCONTROLLER_H
#define UPDATECURRENTASSETVALUESDIALOGCONTROLLER_H

#include <QString>

class AssetInterface;

class UpdateCurrentAssetValuesDialogController
{
public:
    UpdateCurrentAssetValuesDialogController(AssetInterface& localAssetInterface);
    QString getDialogTitle() const;

private:
    AssetInterface& assetInterface;
};

#endif // UPDATECURRENTASSETVALUESDIALOGCONTROLLER_H
