#ifndef MONTHLYBUDGETSUMMARYDIALOGCONTROLLER_H
#define MONTHLYBUDGETSUMMARYDIALOGCONTROLLER_H

#include <QString>

class ExpenseInterface;
class IncomeInterface;
class InvestmentInterface;
class MortgageInterface;

class MonthlyBudgetSummaryDialogController
{
public:
    MonthlyBudgetSummaryDialogController(ExpenseInterface& localExpenseInterface,
                                         IncomeInterface& localIncomeInterface,
                                         InvestmentInterface& localInvestmentInterface,
                                         MortgageInterface& localMortgageInterface);
    QString getMonthlyCashSaved(int month) const;

private:
    ExpenseInterface& expenseInterface;
    IncomeInterface& incomeInterface;
    InvestmentInterface& investmentInterface;
    MortgageInterface& mortgageInterface;
};

#endif // MONTHLYBUDGETSUMMARYDIALOGCONTROLLER_H
