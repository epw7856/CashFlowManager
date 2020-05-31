#ifndef ASSETSUMMARYDIALOG_H
#define ASSETSUMMARYDIALOG_H

#include "assetlisttablemodel.h"
#include <QDialog>

namespace Ui {
class AssetSummaryDialog;
}

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

    void configureAssetListTable();
};

#endif // ASSETSUMMARYDIALOG_H
