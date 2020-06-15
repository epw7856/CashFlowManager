#ifndef ADDEXPENSETYPEDIALOGCONTROLLER_H
#define ADDEXPENSETYPEDIALOGCONTROLLER_H

#include <QString>

class ExpenseInterface;

class AddExpenseTypeDialogController
{
public:
    AddExpenseTypeDialogController(ExpenseInterface& localExpenseInterface);
    bool verifyTypeName(QString name) const;
    bool verifyBudgetAmount(QString amount, bool zeroAllowed) const;
    bool verifyUniqueTypeName(QString name);
    void addExpenseType(const QString& name, double budgetAmount);
    QString getFixedExpenseBudgetAmount(QString name) const;

private:
    ExpenseInterface& expenseInterface;
};

#endif // ADDEXPENSETYPEDIALOGCONTROLLER_H
