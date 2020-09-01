#ifndef UPDATEMORTGAGEINFODIALOG_H
#define UPDATEMORTGAGEINFODIALOG_H

#include <QDialog>

class MortgageInterface;

namespace Ui {
class UpdateMortgageInfoDialog;
}

class UpdateMortgageInfoDialog : public QDialog
{
    Q_OBJECT

public:
    explicit UpdateMortgageInfoDialog(MortgageInterface& localMortgageInterface, QWidget *parent = nullptr);
    ~UpdateMortgageInfoDialog();

private:
    Ui::UpdateMortgageInfoDialog *ui;
};

#endif // UPDATEMORTGAGEINFODIALOG_H
