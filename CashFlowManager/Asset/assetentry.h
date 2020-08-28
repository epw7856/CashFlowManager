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
    void updateName(const std::string& updatedName);
    void updateType(AssetType updatedType);
    std::map<QDate, double> getValue() const;
    static std::string assetTypeToString(AssetType type);
    static AssetType stringToAssetType(std::string type);

private:
    AssetType type = AssetType::Unknown;
    std::string name = "";
    std::map<QDate, double> value;
};

inline AssetType AssetEntry::getType() const
{
    return type;
}

inline std::string AssetEntry::getName() const
{
    return name;
}

inline void AssetEntry::updateName(const std::string& updatedName)
{
    name = updatedName;
}

inline void AssetEntry::updateType(AssetType updatedType)
{
    type = updatedType;
}

inline std::map<QDate, double> AssetEntry::getValue() const
{
    return value;
}

#endif // ASSETENTRY_H
