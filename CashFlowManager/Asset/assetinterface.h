#ifndef ASSETINTERFACE_H
#define ASSETINTERFACE_H

#include "assetentry.h"
#include <vector>

class AssetInterface
{
    virtual std::vector<AssetEntry> getAssetList() const = 0;
    virtual std::vector<AssetEntry> getAssetListByType(AssetType type) const = 0;

};

#endif // ASSETINTERFACE_H
