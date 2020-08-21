#ifndef UPDATEAUTOMATICMONTHLYPAYMENTDIALOGCONTROLLER_H
#define UPDATEAUTOMATICMONTHLYPAYMENTDIALOGCONTROLLER_H

class ExpenseInterface;
class QString;

class UpdateAutomaticMonthlyPaymentsDialogController
{
public:
    UpdateAutomaticMonthlyPaymentsDialogController(ExpenseInterface& localExpenseInterface);
    bool verifyAccountName(QString description) const;
    bool verifyPaymentDescription(QString description) const;
    bool verifyTransactionAmount(QString amount) const;
    void addAutomaticMonthlyPayment(const QString& account, const QString& description, double amount);
    bool deleteAutomaticMonthlyPayment(const QString& account, const QString& description, double amount);

private:
    ExpenseInterface& expenseInterface;
};

#endif // UPDATEAUTOMATICMONTHLYPAYMENTDIALOGCONTROLLER_H
