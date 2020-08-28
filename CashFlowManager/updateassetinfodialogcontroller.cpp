#include "assetentry.h"
#include "assetinterface.h"
#include "currencyutilities.h"
#include "updateassetinfodialogcontroller.h"
#include "validator.h"

UpdateAssetInfoDialogController::UpdateAssetInfoDialogController(AssetInterface& localAssetInterface)
:
    assetInterface(localAssetInterface)
{
    date.setDate(QDate::currentDate().year(), QDate::currentDate().month(), 1);
}

QString UpdateAssetInfoDialogController::getMonthString(int previousMonth) const
{
    return (date.addMonths(-1 * previousMonth).toString("MMMM yyyy") + ":  $");
}

QString UpdateAssetInfoDialogController::getAssetValue(const QString& assetName, int previousMonth) const
{
    double amount = assetInterface.getAssetValue(assetName.toStdString(),
                                                 date.addMonths(-1 * previousMonth).year(),
                                                 date.addMonths(-1 * previousMonth).month());
    return QString::fromStdString(CurrencyUtilities::formatDouble(amount));
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

bool UpdateAssetInfoDialogController::isAssetTypeLiquid(const QString& assetName) const
{
    return (assetInterface.getAssetByName(assetName.toStdString())->getType() == AssetType::Liquid);
}

void UpdateAssetInfoDialogController::deleteAsset(const QString& assetName)
{
    assetInterface.deleteAsset(assetName.toStdString());
}

bool UpdateAssetInfoDialogController::verifyAssetValue(QString value) const
{
    return Validator::verifyDoubleAmount(value, 10000000.00, true);
}

bool UpdateAssetInfoDialogController::verifyAssetName(const QString& assetName) const
{
    return !assetName.isEmpty();
}

void UpdateAssetInfoDialogController::updateAsset(const QString& currentAssetName,
                                                  const QString& updatedAssetName,
                                                  AssetType type,
                                                  std::vector<QString>& values)
{
    assetInterface.updateAssetInfo(currentAssetName.toStdString(), updatedAssetName.toStdString(), type);


}
