#include "assetinterface.h"
#include "assetsummarydialogcontroller.h"
#include "currencyutilities.h"

AssetSummaryDialogController::AssetSummaryDialogController(AssetInterface& localAssetInterface)
:
    assetInterface(localAssetInterface),
    currentDate(QDate::currentDate())
{

}

std::string AssetSummaryDialogController::getCurrentLiquidAssetAmount() const
{
    return (CurrencyUtilities::formatCurrency(assetInterface.getAssetTotalValueByType(AssetType::Liquid, currentDate.year(), currentDate.month())));
}

std::string AssetSummaryDialogController::getYearlyChange(bool netWorthFlag, AssetType type) const
{
    QDate startDate(QDate::currentDate().year(), 1, 1);

    double currentValue = 0.0, previousValue = 0.0;

    if(!netWorthFlag && type != AssetType::Unknown)
    {
        currentValue = assetInterface.getAssetTotalValueByType(type, currentDate.year(), currentDate.month());
        previousValue = assetInterface.getAssetTotalValueByType(type, startDate.year(), startDate.month());
    }
    else
    {
        currentValue = assetInterface.getAssetTotalValueByType(AssetType::Liquid, currentDate.year(), currentDate.month()) +
                       assetInterface.getAssetTotalValueByType(AssetType::Illiquid, currentDate.year(), currentDate.month());

        previousValue = assetInterface.getAssetTotalValueByType(AssetType::Liquid, startDate.year(), startDate.month()) +
                               assetInterface.getAssetTotalValueByType(AssetType::Illiquid, startDate.year(), startDate.month());
    }

    if((previousValue > 0) && (currentDate.month() != 1))
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
    return (CurrencyUtilities::formatCurrency(assetInterface.getAssetTotalValueByType(AssetType::Illiquid, currentDate.year(), currentDate.month())));
}

std::string AssetSummaryDialogController::getCurrentNetWorthAmount() const
{
    double liquidValue = assetInterface.getAssetTotalValueByType(AssetType::Liquid, currentDate.year(), currentDate.month());
    double illiquidValue = assetInterface.getAssetTotalValueByType(AssetType::Illiquid, currentDate.year(), currentDate.month());
    return (CurrencyUtilities::formatCurrency(liquidValue + illiquidValue));
}

std::vector<std::pair<int, double>> AssetSummaryDialogController::getMonthlyNetWorthTotals() const
{
    std::vector<std::pair<int, double>> totals;
    for(int i = 0; i < currentDate.month(); ++i)
    {
        double netWorth = assetInterface.getAssetTotalValueByType(AssetType::Liquid, currentDate.year(), i + 1) +
                          assetInterface.getAssetTotalValueByType(AssetType::Illiquid, currentDate.year(), i + 1);
        totals.push_back({i, netWorth});
    }
    return totals;
}
