#ifndef ADDINVESTMENTTRANSACTIONDIALOG_H
#define ADDINVESTMENTTRANSACTIONDIALOG_H

#include <QDialog>

namespace Ui {
class AddInvestmentTransactionDialog;
}

class AddInvestmentTransactionDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddInvestmentTransactionDialog(QWidget *parent = nullptr);
    ~AddInvestmentTransactionDialog();

private:
    Ui::AddInvestmentTransactionDialog *ui;
};

#endif // ADDINVESTMENTTRANSACTIONDIALOG_H
