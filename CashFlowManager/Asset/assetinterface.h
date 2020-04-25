#ifndef ASSETINTERFACE_H
#define ASSETINTERFACE_H

#include "assettype.h"
#include <vector>

class AssetEntry;

class AssetInterface
{
public:
    virtual ~AssetInterface() = default;
    virtual std::vector<AssetEntry*> getAssetList() const = 0;
    virtual std::vector<AssetEntry*> getAssetListByType(AssetType type) const = 0;
};

#endif // ASSETINTERFACE_H
