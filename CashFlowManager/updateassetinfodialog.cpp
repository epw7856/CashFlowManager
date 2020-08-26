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

    connect(ui->comboBoxAssets, SIGNAL(currentTextChanged(QString)), this, SLOT(assetTypeSelectionChanged(QString)));

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
        disableActions();
    }
    else
    {
        ui->comboBoxAssets->insertItem(0, "<Asset Types>");
    }

    ui->comboBoxAssets->setCurrentIndex(0);
}

void UpdateAssetInfoDialog::disableActions()
{
    ui->pushButtonUpdateAsset->setEnabled(false);
    ui->pushButtonDeleteAsset->setEnabled(false);
    ui->lineEditAssetName->setEnabled(false);
    ui->lineEditMonth1->setEnabled(false);
    ui->lineEditMonth2->setEnabled(false);
    ui->lineEditMonth3->setEnabled(false);
    ui->lineEditMonth4->setEnabled(false);
    ui->lineEditMonth5->setEnabled(false);
    ui->lineEditMonth6->setEnabled(false);
    ui->lineEditMonth7->setEnabled(false);
    ui->lineEditMonth8->setEnabled(false);
    ui->lineEditMonth9->setEnabled(false);
    ui->lineEditMonth10->setEnabled(false);
    ui->lineEditMonth11->setEnabled(false);
    ui->lineEditMonth12->setEnabled(false);
}
