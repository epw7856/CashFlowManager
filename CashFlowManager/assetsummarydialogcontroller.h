#ifndef ASSETSUMMARYDIALOGCONTROLLER_H
#define ASSETSUMMARYDIALOGCONTROLLER_H

#include "assettype.h"
#include <string>

class AssetInterface;

class AssetSummaryDialogController
{
public:
    AssetSummaryDialogController(AssetInterface& localAssetInterface);
    std::string getCurrentLiquidAssetAmount() const;
    std::string getCurrentIlliquidAssetAmount() const;
    std::string getYearlyChange(bool netWorthFlag, AssetType type = AssetType::Unknown) const;
    std::string getCurrentNetWorthAmount() const;

private:
    AssetInterface& assetInterface;
};

#endif // ASSETSUMMARYDIALOGCONTROLLER_H
