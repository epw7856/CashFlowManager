#include <QDate>
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

    connect(ui->pushButtonExit, &QPushButton::clicked, this, &UpdateAssetInfoDialog::onPushButtonExitClicked);
    connect(ui->pushButtonUpdateAsset, &QPushButton::clicked, this, &UpdateAssetInfoDialog::onPushButtonUpdateAssetClicked);
    connect(ui->pushButtonDeleteAsset, &QPushButton::clicked, this, &UpdateAssetInfoDialog::onPushButtonDeleteAssetClicked);
    connect(ui->comboBoxAssets, SIGNAL(currentTextChanged(QString)), this, SLOT(assetTypeSelectionChanged(QString)));

    setDateLabels();
    updateComboBox();
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
        setEnabled(true);

        ui->lineEditAssetName->setText(type);
        bool checked = controller->isAssetTypeLiquid(ui->lineEditAssetName->text());
        ui->radioButtonLiquid->setChecked(checked);
        ui->radioButtonIlliquid->setChecked(!checked);
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

}

void UpdateAssetInfoDialog::setDateLabels()
{
    QDate currentMonth(QDate::currentDate().year(), QDate::currentDate().month(), 1);

    ui->labelMonth1->setText(currentMonth.addMonths(-11).toString("MMMM yyyy") + ":  $");
    ui->labelMonth2->setText(currentMonth.addMonths(-10).toString("MMMM yyyy") + ":  $");
    ui->labelMonth3->setText(currentMonth.addMonths(-9).toString("MMMM yyyy") + ":  $");
    ui->labelMonth4->setText(currentMonth.addMonths(-8).toString("MMMM yyyy") + ":  $");
    ui->labelMonth5->setText(currentMonth.addMonths(-7).toString("MMMM yyyy") + ":  $");
    ui->labelMonth6->setText(currentMonth.addMonths(-6).toString("MMMM yyyy") + ":  $");
    ui->labelMonth7->setText(currentMonth.addMonths(-5).toString("MMMM yyyy") + ":  $");
    ui->labelMonth8->setText(currentMonth.addMonths(-4).toString("MMMM yyyy") + ":  $");
    ui->labelMonth9->setText(currentMonth.addMonths(-3).toString("MMMM yyyy") + ":  $");
    ui->labelMonth10->setText(currentMonth.addMonths(-2).toString("MMMM yyyy") + ":  $");
    ui->labelMonth11->setText(currentMonth.addMonths(-1).toString("MMMM yyyy") + ":  $");
    ui->labelMonth12->setText(currentMonth.toString("MMMM yyyy") + ":  $");
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
