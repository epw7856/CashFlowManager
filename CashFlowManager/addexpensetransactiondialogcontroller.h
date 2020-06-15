#ifndef ADDEXPENSETRANSACTIONDIALOGCONTROLLER_H
#define ADDEXPENSETRANSACTIONDIALOGCONTROLLER_H

#include <QDate>
#include <QStringList>

class ExpenseInterface;
class MortgageInterface;

class AddExpenseTransactionDialogController
{
public:
    AddExpenseTransactionDialogController(ExpenseInterface& localExpenseInterface, MortgageInterface& localMortgageInterface);
    QStringList getExpenseTypes() const;
    bool verifyTransactionDescription(QString description) const;
    bool verifyTransactionDate(QDate date) const;
    bool verifyTransactionAmount(QString amount, bool zeroAllowed) const;
    void addExpenseTransaction(const QDate& date,
                               const QString& type,
                               const QString& description,
                               double transactionAmount,
                               double additionalPrincipal = 0.0);

private:
    ExpenseInterface& expenseInterface;
    MortgageInterface& mortgageInterface;
};

#endif // ADDEXPENSETRANSACTIONDIALOGCONTROLLER_H
