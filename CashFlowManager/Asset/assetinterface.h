#ifndef ASSETINTERFACE_H
#define ASSETINTERFACE_H

#include "assettype.h"
#include <string>
#include <vector>

class QDate;
class AssetEntry;

class AssetInterface
{
public:
    virtual ~AssetInterface() = default;
    virtual std::vector<AssetEntry*> getAssetList() const = 0;
    virtual std::vector<AssetEntry*> getAssetListByType(AssetType type) const = 0;
    virtual void addAsset(const AssetEntry& entry) = 0;
    virtual void addAssetValue(const std::string& assetName, const std::pair<QDate, double>& valueEntry) = 0;
};

#endif // ASSETINTERFACE_H
