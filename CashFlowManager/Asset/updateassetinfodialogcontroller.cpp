#include "assetentry.h"
#include "assetinterface.h"
#include "currencyutilities.h"
#include <QDate>
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
    if(previousMonth == 0 && !assetInterface.currentMonthValueEnteredForAsset(assetName.toStdString()))
    {
        return QString::fromStdString(CurrencyUtilities::formatDouble(0.0));
    }

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

bool UpdateAssetInfoDialogController::verifyUniqueAssetName(const QString& assetName) const
{
    std::vector<AssetEntry*> assets = assetInterface.getAssetList();

    auto itr = std::find_if(assets.begin(), assets.end(), [=] (const AssetEntry* asset)
    {
        return (QString::fromStdString(asset->getName()).toLower() == assetName.trimmed().toLower());
    });
    return (itr == assets.end());
}

void UpdateAssetInfoDialogController::addAsset(const QString& assetName,
                                               bool isLiquid,
                                               std::vector<QString>& values)
{
    AssetType type;
    (isLiquid) ? type = AssetType::Liquid :
                 type = AssetType::Illiquid;

    AssetEntry entry(type, assetName.trimmed().toStdString(), {});
    assetInterface.addAsset(entry);

    addAssetValues(assetName, values);
}

void UpdateAssetInfoDialogController::updateAsset(const QString& currentAssetName,
                                                  const QString& updatedAssetName,
                                                  bool isLiquid,
                                                  std::vector<QString>& values)
{
    AssetType type;
    (isLiquid) ? type = AssetType::Liquid :
                 type = AssetType::Illiquid;

    assetInterface.updateAssetInfo(currentAssetName.toStdString(), updatedAssetName.trimmed().toStdString(), type);

    addAssetValues(updatedAssetName, values);
}

void UpdateAssetInfoDialogController::addAssetValues(const QString& assetName, std::vector<QString>& values)
{
    for(quint32 i = 0; i < values.size(); ++i)
    {
        QDate date(QDate::currentDate().year(), QDate::currentDate().month(), 1);
        assetInterface.addAssetValue(assetName.toStdString(), {date.addMonths(-1 * i), values[i].remove(',').toDouble()});
    }
}
