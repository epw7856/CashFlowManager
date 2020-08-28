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
    virtual AssetEntry* getAssetByName(const std::string& assetName) const = 0;
    virtual std::vector<AssetEntry*> getAssetList() const = 0;
    virtual std::vector<AssetEntry*> getAssetListByType(AssetType type) const = 0;
    virtual void addAsset(const AssetEntry& entry) = 0;
    virtual void addAssetValue(const std::string& assetName, const std::pair<QDate, double>& valueEntry) = 0;
    virtual void updateAssetInfo(const std::string& currentAssetName, const std::string& updatedAssetName, AssetType type) = 0;
    virtual void deleteAsset(const std::string& assetName) = 0;
    virtual double getAssetValue(const std::string assetName, int year, int month) const = 0;
    virtual double getAssetTotalValueByType(AssetType type, int year, int month) const = 0;
    virtual bool currentMonthValuesEntered() const = 0;
};

#endif // ASSETINTERFACE_H
