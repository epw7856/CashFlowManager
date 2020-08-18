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

std::vector<double> AssetSummaryDialogController::getPastYearNetWorthTotals() const
{
    std::vector<double> totals;
    QDate date(QDate::currentDate());

    if(!assetInterface.currentMonthValuesEntered())
    {
        date = date.addMonths(-1);
    }

    for(int i = 0; i < 12; ++i)
    {
        double netWorth = assetInterface.getAssetTotalValueByType(AssetType::Liquid, date.year(), date.month()) +
                          assetInterface.getAssetTotalValueByType(AssetType::Illiquid, date.year(), date.month());
        totals.push_back(netWorth);
        date = date.addMonths(-1);
    }
    return totals;
}

bool AssetSummaryDialogController::getCurrentMonthValuesEntered() const
{
    return assetInterface.currentMonthValuesEntered();
}

std::pair<double, double> AssetSummaryDialogController::getPastYearMinandMaxNetWorth() const
{
    std::vector<double> totals = getPastYearNetWorthTotals();
    double min = 0.0, max = 0.0;
    min = totals[0];

    for(const auto& i : totals)
    {
        if(i > max)
        {
            max = i;
        }

        if(i < min)
        {
            min = i;
        }
    }

    return {min, max};
}
