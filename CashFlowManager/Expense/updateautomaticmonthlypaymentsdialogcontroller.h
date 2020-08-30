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
    bool verifyUniquePaymentName(QString account, QString description) const;
    void addAutomaticMonthlyPayment(const QString& account, const QString& description, double amount);
    void deleteAutomaticMonthlyPayment(const QString& account, const QString& description, double amount);
    void updateAutomaticMonthlyPayment(const QString& existingAccount,
                                       const QString& existingDescription,
                                       double existingAmount,
                                       const QString& updatedAccount,
                                       const QString& updatedDescription,
                                       double updatedAmount);

private:
    ExpenseInterface& expenseInterface;
};

#endif // UPDATEAUTOMATICMONTHLYPAYMENTDIALOGCONTROLLER_H
