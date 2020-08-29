#ifndef UPDATECURRENTASSETVALUESDIALOG_H
#define UPDATECURRENTASSETVALUESDIALOG_H

#include <memory>
#include <QDialog>

class AssetInterface;
class UpdateCurrentAssetValuesDialogController;

namespace Ui {
class UpdateCurrentAssetValuesDialog;
}

class UpdateCurrentAssetValuesDialog : public QDialog
{
    Q_OBJECT

public:
    explicit UpdateCurrentAssetValuesDialog(AssetInterface& localAssetInterace, QWidget *parent = nullptr);
    ~UpdateCurrentAssetValuesDialog();

signals:
    void dialogClosed();

private slots:
    void onPushButtonExitClicked();
    void onPushButtonUpdateClicked();

public slots:
    void closeEvent(QCloseEvent*) override;

private:
    Ui::UpdateCurrentAssetValuesDialog *ui;
    std::unique_ptr<UpdateCurrentAssetValuesDialogController> controller;
};

#endif // UPDATECURRENTASSETVALUESDIALOG_H
