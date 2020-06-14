#ifndef ADDEXPENSETRANSACTIONDIALOGCONTROLLER_H
#define ADDEXPENSETRANSACTIONDIALOGCONTROLLER_H

#include <QStringList>

class ExpenseInterface;
class MortgageInterface;

class AddExpenseTransactionDialogController
{
public:
    AddExpenseTransactionDialogController(ExpenseInterface& localExpenseInterface, MortgageInterface& localMortgageInterface);
    QStringList getExpenseTypes() const;

private:
    ExpenseInterface& expenseInterface;
    MortgageInterface& mortgageInterface;
};

#endif // ADDEXPENSETRANSACTIONDIALOGCONTROLLER_H
