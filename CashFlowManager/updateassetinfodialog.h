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
    explicit UpdateAssetInfoDialog(AssetInterface& localAssetInterace, QWidget *parent = nullptr);
    ~UpdateAssetInfoDialog();

signals:
    void dialogClosed();

public slots:
    void closeEvent(QCloseEvent*) override;

private slots:
    void assetTypeSelectionChanged(QString type);

private:
    Ui::UpdateAssetInfoDialog *ui;
    std::unique_ptr<UpdateAssetInfoDialogController> controller;

    void setDateLabels();
    void updateComboBox();
    void disableActions();
};

#endif // UPDATEASSETINFODIALOG_H
