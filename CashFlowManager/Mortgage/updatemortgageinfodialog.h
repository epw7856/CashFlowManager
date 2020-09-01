#ifndef UPDATEMORTGAGEINFODIALOG_H
#define UPDATEMORTGAGEINFODIALOG_H

#include <memory>
#include <QDialog>

class MortgageInterface;
class UpdateMortgageInfoDialogController;

namespace Ui {
class UpdateMortgageInfoDialog;
}

class UpdateMortgageInfoDialog : public QDialog
{
    Q_OBJECT

public:
    explicit UpdateMortgageInfoDialog(MortgageInterface& localMortgageInterface, QWidget *parent = nullptr);
    ~UpdateMortgageInfoDialog();

signals:
    void dialogClosed();

public slots:
    void onPushButtonExitClicked();
    void onPushButtonUpdateClicked();
    void closeEvent(QCloseEvent*) override;

private:
    Ui::UpdateMortgageInfoDialog *ui;
    std::unique_ptr<UpdateMortgageInfoDialogController> controller;

    void populateFields();
};

#endif // UPDATEMORTGAGEINFODIALOG_H
