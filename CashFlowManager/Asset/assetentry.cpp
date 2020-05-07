#include "assetentry.h"

AssetEntry::AssetEntry
(
    AssetType inputType,
    std::string inputName,
    std::map<QDate, double> inputNetValue
)
:
    type(inputType),
    name(inputName),
    netValue(std::move(inputNetValue))
{

}

void AssetEntry::addValueEntry(const std::pair<QDate, double>& entry)
{
    netValue.insert(entry);
}

std::string AssetEntry::assetTypeToString(AssetType type)
{
    if(type == AssetType::Liquid)
    {
        return "Liquid";
    }
    else if(type == AssetType::Illiquid)
    {
        return "Illiquid";
    }

    return "Unknown";
}

AssetType AssetEntry::stringToAssetType(std::string type)
{
    if(type == "liquid")
    {
        return AssetType::Liquid;
    }
    else if(type == "illiquid")
    {
        return AssetType::Illiquid;
    }

    return AssetType::Unknown;
}