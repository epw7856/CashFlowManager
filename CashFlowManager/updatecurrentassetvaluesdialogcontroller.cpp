#include "assetinterface.h"
#include <QDate>
#include "updatecurrentassetvaluesdialogcontroller.h"

UpdateCurrentAssetValuesDialogController::UpdateCurrentAssetValuesDialogController(AssetInterface& localAssetInterface)
:
    assetInterface(localAssetInterface)
{

}

QString UpdateCurrentAssetValuesDialogController::getDialogTitle() const
{
    return (QDate::currentDate().toString("MMMM yyyy") + " Asset Values");
}
