#include "assetinterface.h"
#include "assetsummarydialogcontroller.h"
#include "currencyutilities.h"
#include <QDate>

AssetSummaryDialogController::AssetSummaryDialogController(AssetInterface& localAssetInterface)
:
    assetInterface(localAssetInterface)
{

}

std::string AssetSummaryDialogController::getCurrentLiquidAssetAmount() const
{
    QDate date(QDate::currentDate());
    return (CurrencyUtilities::formatCurrency(assetInterface.getAssetTotalValueByType(AssetType::Liquid, date.year(), date.month())));
}

std::string AssetSummaryDialogController::getYearlyChange(bool netWorthFlag, AssetType type) const
{
    QDate date(QDate::currentDate());
    QDate previousDate = date.addMonths(-1);

    double currentValue = 0.0, previousValue = 0.0;

    if(!netWorthFlag && type != AssetType::Unknown)
    {
        currentValue = assetInterface.getAssetTotalValueByType(type, date.year(), date.month());
        previousValue = assetInterface.getAssetTotalValueByType(type, previousDate.year(), previousDate.month());
    }
    else
    {
        currentValue = assetInterface.getAssetTotalValueByType(AssetType::Liquid, date.year(), date.month()) +
                       assetInterface.getAssetTotalValueByType(AssetType::Illiquid, date.year(), date.month());

        previousValue = assetInterface.getAssetTotalValueByType(AssetType::Liquid, previousDate.year(), previousDate.month()) +
                               assetInterface.getAssetTotalValueByType(AssetType::Illiquid, previousDate.year(), previousDate.month());
    }


    if(previousValue > 0)
    {
        return (CurrencyUtilities::formatRatio((currentValue - previousValue) / previousValue));
    }
    else
    {
        return "N/A";
    }
}

std::string AssetSummaryDialogController::getCurrentIlliquidAssetAmount() const
{
    QDate date(QDate::currentDate());
    return (CurrencyUtilities::formatCurrency(assetInterface.getAssetTotalValueByType(AssetType::Illiquid, date.year(), date.month())));
}

std::string AssetSummaryDialogController::getCurrentNetWorthAmount() const
{
    QDate date(QDate::currentDate());
    double liquidValue = assetInterface.getAssetTotalValueByType(AssetType::Liquid, date.year(), date.month());
    double illiquidValue = assetInterface.getAssetTotalValueByType(AssetType::Illiquid, date.year(), date.month());
    return (CurrencyUtilities::formatCurrency(liquidValue + illiquidValue));
}
