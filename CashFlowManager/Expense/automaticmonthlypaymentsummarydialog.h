#ifndef AUTOMATICMONTHLYPAYMENTSUMMARYDIALOG_H
#define AUTOMATICMONTHLYPAYMENTSUMMARYDIALOG_H

#include "automaticmonthlypaymenttablemodel.h"
#include <QDialog>

namespace Ui {
class AutomaticMonthlyPaymentSummaryDialog;
}

class AutomaticMonthlyPaymentSummaryDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AutomaticMonthlyPaymentSummaryDialog(ExpenseInterface& localExpenseInterface, QWidget* parent = nullptr);
    ~AutomaticMonthlyPaymentSummaryDialog();

public slots:
    void onPushButtonExitClicked();

private:
    Ui::AutomaticMonthlyPaymentSummaryDialog *ui;
    AutomaticMonthlyPaymentTableModel autoPaymentTableModel;

    void configureAutoMonthlyPaymentTable();
};

#endif // AUTOMATICMONTHLYPAYMENTSUMMARYDIALOG_H
