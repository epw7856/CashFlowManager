#ifndef ASSETENTRY_H
#define ASSETENTRY_H

#include <map>
#include <QDate>

enum class AssetType
{
    Unknown,
    Liquid,
    Illiquid
};

struct AssetEntry
{
    AssetType Type = AssetType::Unknown;
    std::string Name = "";
    std::map<QDate, double> NetValue;
};

#endif // ASSETENTRY_H
