#ifndef UPDATEAUTOMATICMONTHLYPAYMENTDIALOGCONTROLLER_H
#define UPDATEAUTOMATICMONTHLYPAYMENTDIALOGCONTROLLER_H

class ExpenseInterface;
class QString;

class UpdateAutomaticMonthlyPaymentsDialogController
{
public:
    UpdateAutomaticMonthlyPaymentsDialogController(ExpenseInterface& localExpenseInterface);
    bool verifyPaymentDescription(QString description) const;
    bool verifyTransactionAmount(QString amount) const;

private:
    ExpenseInterface& expenseInterface;
};

#endif // UPDATEAUTOMATICMONTHLYPAYMENTDIALOGCONTROLLER_H
