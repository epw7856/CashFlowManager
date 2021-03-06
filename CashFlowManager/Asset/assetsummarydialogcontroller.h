#ifndef ASSETSUMMARYDIALOGCONTROLLER_H
#define ASSETSUMMARYDIALOGCONTROLLER_H

#include "assettype.h"
#include <QDate>
#include <string>
#include <vector>

class AssetInterface;

class AssetSummaryDialogController
{
public:
    AssetSummaryDialogController(AssetInterface& localAssetInterface);
    std::string getCurrentLiquidAssetAmount() const;
    std::string getCurrentIlliquidAssetAmount() const;
    std::string getYearlyChange(bool netWorthFlag, AssetType type = AssetType::Unknown) const;
    std::string getCurrentNetWorthAmount() const;
    std::vector<double> getPastYearNetWorthTotals() const;
    bool getCurrentMonthValuesEntered() const;
    std::pair<double, double> getPastYearMinandMaxNetWorth() const;

private:
    AssetInterface& assetInterface;
    QDate currentDate;
};

#endif // ASSETSUMMARYDIALOGCONTROLLER_H
