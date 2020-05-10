#ifndef YEARLYBUDGETSUMMARYDIALOG_H
#define YEARLYBUDGETSUMMARYDIALOG_H

#include <QDialog>
#include "yearlyexpensetablemodel.h"
#include "yearlyinvestmenttablemodel.h"

class ExpenseInterface;
class InvestmentInterface;

namespace Ui {
class YearlyBudgetSummaryDialog;
}

class YearlyBudgetSummaryDialog : public QDialog
{
    Q_OBJECT

public:
    explicit YearlyBudgetSummaryDialog(ExpenseInterface& localExpenseInterface,
                                       InvestmentInterface& localInvestmentInterface,
                                       QWidget* parent = nullptr);
    ~YearlyBudgetSummaryDialog();

public slots:
    void onPushButtonExitClicked();

private:
    Ui::YearlyBudgetSummaryDialog* ui;
    YearlyExpenseTableModel expenseTableModel;
    YearlyInvestmentTableModel investmentTableModel;

    void configureExpenseSummaryTable();
    void configureInvestmentSummaryTable();
};

#endif // YEARLYBUDGETSUMMARYDIALOG_H
