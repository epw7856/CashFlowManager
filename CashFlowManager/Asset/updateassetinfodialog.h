#ifndef UPDATEASSETINFODIALOG_H
#define UPDATEASSETINFODIALOG_H

#include <memory>
#include <QDialog>

class AssetInterface;
class UpdateAssetInfoDialogController;

namespace Ui {
class UpdateAssetInfoDialog;
}

class UpdateAssetInfoDialog : public QDialog
{
    Q_OBJECT

public:
    explicit UpdateAssetInfoDialog(AssetInterface& localAssetInterace, bool addNewAsset, QWidget *parent = nullptr);
    ~UpdateAssetInfoDialog();

signals:
    void dialogClosed();

public slots:
    void closeEvent(QCloseEvent*) override;

private slots:
    void assetTypeSelectionChanged(QString type);
    void onPushButtonExitClicked();
    void onPushButtonAddAssetClicked();
    void onPushButtonUpdateAssetClicked();
    void onPushButtonDeleteAssetClicked();

private:
    Ui::UpdateAssetInfoDialog *ui;
    std::unique_ptr<UpdateAssetInfoDialogController> controller;
    QString currentAsset = "";

    void setDateLabels();
    void updateComboBox(quint32 currentIndex = 0);
    void updateValues();
    void setEnabled(bool enabled);
    bool verifyAmounts();
    void populateVectorWithValues(std::vector<QString>& values);
};

#endif // UPDATEASSETINFODIALOG_H
