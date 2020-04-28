#ifndef ASSETENTRY_H
#define ASSETENTRY_H

#include "assettype.h"
#include <map>
#include <QDate>

class AssetEntry
{
public:
    AssetEntry(AssetType inputType, std::string inputName, std::map<QDate, double> inputNetValue);

    void addValueEntry(const std::pair<QDate, double>& entry);

    AssetType getType() const;

    std::string getName() const;

    std::map<QDate, double> getNetValue() const;

    static std::string assetTypeToString(AssetType type);

    static AssetType stringToAssetType(std::string type);

private:
    AssetType type = AssetType::Unknown;
    std::string name = "";
    std::map<QDate, double> netValue;
};

#endif // ASSETENTRY_H
