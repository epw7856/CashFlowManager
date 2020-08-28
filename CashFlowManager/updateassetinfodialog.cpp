#include <QMessageBox>
#include "updateassetinfodialog.h"
#include "updateassetinfodialogcontroller.h"
#include "ui_updateassetinfodialog.h"

UpdateAssetInfoDialog::UpdateAssetInfoDialog(AssetInterface& localAssetInterace, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::UpdateAssetInfoDialog),
    controller(std::make_unique<UpdateAssetInfoDialogController>(localAssetInterace))
{
    ui->setupUi(this);
    setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);
    setWindowFlag(Qt::WindowMinMaxButtonsHint);

    updateComboBox();
    setDateLabels();
    setEnabled(false);

    connect(ui->pushButtonExit, &QPushButton::clicked, this, &UpdateAssetInfoDialog::onPushButtonExitClicked);
    connect(ui->pushButtonUpdateAsset, &QPushButton::clicked, this, &UpdateAssetInfoDialog::onPushButtonUpdateAssetClicked);
    connect(ui->pushButtonDeleteAsset, &QPushButton::clicked, this, &UpdateAssetInfoDialog::onPushButtonDeleteAssetClicked); 
    connect(ui->comboBoxAssets, SIGNAL(currentTextChanged(QString)), this, SLOT(assetTypeSelectionChanged(QString)));
}

UpdateAssetInfoDialog::~UpdateAssetInfoDialog()
{
    delete ui;
}

void UpdateAssetInfoDialog::closeEvent(QCloseEvent *)
{
    emit dialogClosed();
    accept();
}

void UpdateAssetInfoDialog::assetTypeSelectionChanged(QString type)
{
    if(ui->comboBoxAssets->currentIndex() > 0)
    {
        currentAsset = ui->comboBoxAssets->currentText();
        setEnabled(true);
        ui->lineEditAssetName->setText(type);
        bool checked = controller->isAssetTypeLiquid(currentAsset);
        ui->radioButtonLiquid->setChecked(checked);
        ui->radioButtonIlliquid->setChecked(!checked);
        updateValues();
    }
    else
    {
        setEnabled(false);
    }
}

void UpdateAssetInfoDialog::onPushButtonExitClicked()
{
    close();
}

void UpdateAssetInfoDialog::onPushButtonUpdateAssetClicked()
{

}

void UpdateAssetInfoDialog::onPushButtonDeleteAssetClicked()
{
    if(ui->comboBoxAssets->currentIndex() > 0)
    {
        int returnValue = QMessageBox::warning(this, tr("Confirm Selection"), "Are you sure you want to delete asset type '" + currentAsset + "'?", QMessageBox::Yes | QMessageBox::No);

        switch (returnValue)
        {
          case QMessageBox::Yes:

              controller->deleteAsset(currentAsset);
              QMessageBox::information(this, tr("Success"), "<p align='center'>Successfully deleted asset '" + currentAsset + "'.</p>", QMessageBox::Ok);

            break;

          case QMessageBox::No:
              return;

          default:
              return;
        }
    }
    else
    {
        QMessageBox::critical(this, tr("Error"), "<p align='center'>No asset type has been selected.<br>Please select an asset type to be deleted.</p>", QMessageBox::Ok);
        return;
    }

    ui->comboBoxAssets->setCurrentIndex(0);
    updateComboBox();
}

void UpdateAssetInfoDialog::setDateLabels()
{
    ui->labelMonth1->setText(controller->getMonthString(11));
    ui->labelMonth2->setText(controller->getMonthString(10));
    ui->labelMonth3->setText(controller->getMonthString(9));
    ui->labelMonth4->setText(controller->getMonthString(8));
    ui->labelMonth5->setText(controller->getMonthString(7));
    ui->labelMonth6->setText(controller->getMonthString(6));
    ui->labelMonth7->setText(controller->getMonthString(5));
    ui->labelMonth8->setText(controller->getMonthString(4));
    ui->labelMonth9->setText(controller->getMonthString(3));
    ui->labelMonth10->setText(controller->getMonthString(2));
    ui->labelMonth11->setText(controller->getMonthString(1));
    ui->labelMonth12->setText(controller->getMonthString(0));
}

void UpdateAssetInfoDialog::updateComboBox()
{
    ui->comboBoxAssets->clear();
    ui->comboBoxAssets->addItems(controller->getAssetTypes());
    if(ui->comboBoxAssets->count() == 0)
    {
        ui->comboBoxAssets->insertItem(0, "No Assets Found");
        setEnabled(false);
    }
    else
    {
        ui->comboBoxAssets->insertItem(0, "<Asset Types>");
    }

    ui->comboBoxAssets->setCurrentIndex(0);
}

void UpdateAssetInfoDialog::updateValues()
{
    ui->lineEditMonth1->setText(controller->getAssetValue(currentAsset, 11));
    ui->lineEditMonth2->setText(controller->getAssetValue(currentAsset, 10));
    ui->lineEditMonth3->setText(controller->getAssetValue(currentAsset, 9));
    ui->lineEditMonth4->setText(controller->getAssetValue(currentAsset, 8));
    ui->lineEditMonth5->setText(controller->getAssetValue(currentAsset, 7));
    ui->lineEditMonth6->setText(controller->getAssetValue(currentAsset, 6));
    ui->lineEditMonth7->setText(controller->getAssetValue(currentAsset, 5));
    ui->lineEditMonth8->setText(controller->getAssetValue(currentAsset, 4));
    ui->lineEditMonth9->setText(controller->getAssetValue(currentAsset, 3));
    ui->lineEditMonth10->setText(controller->getAssetValue(currentAsset, 2));
    ui->lineEditMonth11->setText(controller->getAssetValue(currentAsset, 1));
    ui->lineEditMonth12->setText(controller->getAssetValue(currentAsset, 0));
}

void UpdateAssetInfoDialog::setEnabled(bool enabled)
{
    ui->lineEditAssetName->clear();
    ui->pushButtonUpdateAsset->setEnabled(enabled);
    ui->pushButtonDeleteAsset->setEnabled(enabled);
    ui->lineEditAssetName->setEnabled(enabled);
    ui->radioButtonLiquid->setEnabled(enabled);
    ui->radioButtonIlliquid->setEnabled(enabled);
    ui->radioButtonLiquid->setChecked(true);

    ui->lineEditMonth1->setText("0.00");
    ui->lineEditMonth2->setText("0.00");
    ui->lineEditMonth3->setText("0.00");
    ui->lineEditMonth4->setText("0.00");
    ui->lineEditMonth5->setText("0.00");
    ui->lineEditMonth6->setText("0.00");
    ui->lineEditMonth7->setText("0.00");
    ui->lineEditMonth8->setText("0.00");
    ui->lineEditMonth9->setText("0.00");
    ui->lineEditMonth10->setText("0.00");
    ui->lineEditMonth11->setText("0.00");
    ui->lineEditMonth12->setText("0.00");

    ui->lineEditMonth1->setEnabled(enabled);
    ui->lineEditMonth2->setEnabled(enabled);
    ui->lineEditMonth3->setEnabled(enabled);
    ui->lineEditMonth4->setEnabled(enabled);
    ui->lineEditMonth5->setEnabled(enabled);
    ui->lineEditMonth6->setEnabled(enabled);
    ui->lineEditMonth7->setEnabled(enabled);
    ui->lineEditMonth8->setEnabled(enabled);
    ui->lineEditMonth9->setEnabled(enabled);
    ui->lineEditMonth10->setEnabled(enabled);
    ui->lineEditMonth11->setEnabled(enabled);
    ui->lineEditMonth12->setEnabled(enabled);
}
