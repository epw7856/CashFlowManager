#ifndef YEARLYINCOMESUMMARYDIALOG_H
#define YEARLYINCOMESUMMARYDIALOG_H

#include <QDialog>
#include "salaryincometablemodel.h"
#include "supplementalincometablemodel.h"

namespace Ui {
class YearlyIncomeSummaryDialog;
}

class YearlyIncomeSummaryDialog : public QDialog
{
    Q_OBJECT

public:
    explicit YearlyIncomeSummaryDialog(IncomeInterface& localIncomeInterface, QWidget *parent = nullptr);
    ~YearlyIncomeSummaryDialog();

public slots:
    void onPushButtonExitClicked();

private:
    Ui::YearlyIncomeSummaryDialog *ui;
    SalaryIncomeTableModel salaryTableModel;
    SupplementalIncomeTableModel supplementalTableModel;

    void configureSalaryTable();
    void configureSupplementalTable();
};

#endif // YEARLYINCOMESUMMARYDIALOG_H
