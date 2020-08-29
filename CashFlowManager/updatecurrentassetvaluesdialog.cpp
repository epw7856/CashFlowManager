#include "updatecurrentassetvaluesdialog.h"
#include "updatecurrentassetvaluesdialogcontroller.h"
#include "ui_updatecurrentassetvaluesdialog.h"

UpdateCurrentAssetValuesDialog::UpdateCurrentAssetValuesDialog(AssetInterface& localAssetInterace, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::UpdateCurrentAssetValuesDialog),
    controller(std::make_unique<UpdateCurrentAssetValuesDialogController>(localAssetInterace))
{
    ui->setupUi(this);
    setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);
    setWindowFlag(Qt::WindowMinMaxButtonsHint);

    ui->labelDialogTitle->setText(controller->getDialogTitle());

    connect(ui->pushButtonExit, &QPushButton::clicked, this, &UpdateCurrentAssetValuesDialog::onPushButtonExitClicked);
    connect(ui->pushButtonUpdate, &QPushButton::clicked, this, &UpdateCurrentAssetValuesDialog::onPushButtonUpdateClicked);
}

UpdateCurrentAssetValuesDialog::~UpdateCurrentAssetValuesDialog()
{
    delete ui;
}

void UpdateCurrentAssetValuesDialog::onPushButtonExitClicked()
{
    close();
}

void UpdateCurrentAssetValuesDialog::onPushButtonUpdateClicked()
{

}

void UpdateCurrentAssetValuesDialog::closeEvent(QCloseEvent*)
{
    emit dialogClosed();
    accept();
}
