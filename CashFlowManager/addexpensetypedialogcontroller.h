#ifndef ADDEXPENSETYPEDIALOGCONTROLLER_H
#define ADDEXPENSETYPEDIALOGCONTROLLER_H

#include <QString>

class ExpenseInterface;
class MortgageInterface;

class AddExpenseTypeDialogController
{
public:
    AddExpenseTypeDialogController(ExpenseInterface& localExpenseInterface, MortgageInterface& localMortgageInterface);
    QStringList getExpenseTypes() const;
    bool verifyTypeName(QString name) const;
    bool verifyBudgetAmount(QString amount, bool zeroAllowed) const;
    bool verifyUniqueTypeName(QString name);
    void addExpenseType(const QString& name, double budgetAmount);
    void deleteExpenseType(const QString& name);
    QString getMonthlyBudgetAmount(QString name) const;
    bool expenseTypeContainsYearlyTransactions(const QString& name);

private:
    ExpenseInterface& expenseInterface;
    MortgageInterface& mortgageInterface;
};

#endif // ADDEXPENSETYPEDIALOGCONTROLLER_H
