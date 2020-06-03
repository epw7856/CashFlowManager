#ifndef ASSETSUMMARYDIALOG_H
#define ASSETSUMMARYDIALOG_H

#include "assetlisttablemodel.h"
#include <memory>
#include <QDialog>

namespace Ui {
class AssetSummaryDialog;
}

class AssetSummaryDialogController;

class AssetSummaryDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AssetSummaryDialog(AssetInterface& localAssetInterface, QWidget *parent = nullptr);
    ~AssetSummaryDialog();

public slots:
    void onPushButtonExitClicked();

private:
    Ui::AssetSummaryDialog *ui;
    AssetListTableModel assetListTable;
    std::unique_ptr<AssetSummaryDialogController> assetSummaryDialogController;

    void configureAssetListTable();
};

#endif // ASSETSUMMARYDIALOG_H
