#ifndef MORTGAGESUMMARYDIALOG_H
#define MORTGAGESUMMARYDIALOG_H

#include "mortgagetablemodel.h"
#include <QDialog>

namespace Ui {
class MortgageSummaryDialog;
}

class MortgageSummaryDialog : public QDialog
{
    Q_OBJECT

public:
    explicit MortgageSummaryDialog(MortgageInterface& localMortgageInterface, QWidget *parent = nullptr);
    ~MortgageSummaryDialog();

public slots:
    void onPushButtonExitClicked();

private:
    void configureMortgageSummaryTable();

    Ui::MortgageSummaryDialog *ui;
    MortgageTableModel mortgageTableModel;
};

#endif // MORTGAGESUMMARYDIALOG_H
