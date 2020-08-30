#ifndef UPDATEASSETINFODIALOGCONTROLLER_H
#define UPDATEASSETINFODIALOGCONTROLLER_H

#include <QDate>
#include <QStringList>
#include <vector>

class AssetInterface;

class UpdateAssetInfoDialogController
{
public:
    UpdateAssetInfoDialogController(AssetInterface& localAssetInterface);
    QString getMonthString(int previousMonth) const;
    QString getAssetValue(const QString& assetName, int previousMonth) const;
    QStringList getAssetTypes() const;
    bool isAssetTypeLiquid(const QString& assetName) const;
    void deleteAsset(const QString& assetName);
    bool verifyAssetValue(QString value) const;
    bool verifyAssetName(const QString& assetName) const;
    bool verifyUniqueAssetName(const QString& assetName) const;
    void addAsset(const QString& assetName,
                  bool isLiquid,
                  std::vector<QString>& values);
    void updateAsset(const QString& currentAssetName,
                     const QString& updatedAssetName,
                     bool isLiquid,
                     std::vector<QString>& values);

private:
    AssetInterface& assetInterface;
    QDate date;

    void addAssetValues(const QString& assetName, std::vector<QString>& values);
};

#endif // UPDATEASSETINFODIALOGCONTROLLER_H
