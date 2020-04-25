#ifndef ASSETENTRY_H
#define ASSETENTRY_H

#include "assettype.h"
#include <map>
#include <QDate>

class AssetEntry
{
public:
    AssetEntry
    (
        AssetType inputType,
        std::string inputName,
        std::map<QDate, double> inputNetValue
    )
    :
        type(inputType),
        name(inputName),
        netValue(std::move(inputNetValue)){}

    AssetType getType() const;

    std::string getName() const;

    std::map<QDate, double> getNetValue() const;

private:
    AssetType type = AssetType::Unknown;
    std::string name = "";
    std::map<QDate, double> netValue;
};

#endif // ASSETENTRY_H

AssetType AssetEntry::getType() const
{
    return type;
}

std::string AssetEntry::getName() const
{
    return name;
}

std::map<QDate, double> AssetEntry::getNetValue() const
{
    return netValue;
}
