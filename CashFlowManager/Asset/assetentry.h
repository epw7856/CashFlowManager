#ifndef ASSETENTRY_H
#define ASSETENTRY_H

#include <map>
#include <QDate>

struct AssetEntry
{
    std::string Name = "";
    std::map<QDate, double> NetValue;
};

#endif // ASSETENTRY_H
