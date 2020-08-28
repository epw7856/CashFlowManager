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
    value(std::move(inputNetValue))
{

}

void AssetEntry::addValueEntry(const std::pair<QDate, double>& entry)
{
    if(value.find(entry.first) != value.end())
    {
        value[entry.first] = entry.second;
    }
    else
    {
        value.insert(entry);
    }
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
