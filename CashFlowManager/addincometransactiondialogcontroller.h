#ifndef ADDINCOMETRANSACTIONDIALOGCONTROLLER_H
#define ADDINCOMETRANSACTIONDIALOGCONTROLLER_H

#include <QDate>

class IncomeInterface;

class AddIncomeTransactionDialogController
{
public:
    AddIncomeTransactionDialogController(IncomeInterface& localIncomeInterface);
    void addSalaryIncomeTransaction(const QDate& date, const double amount, const int overtime);
    void addSupplementalIncomeTransaction(const QDate& date, const QString& description, const double amount);

private:
    IncomeInterface& incomeInterface;
};

#endif // ADDINCOMETRANSACTIONDIALOGCONTROLLER_H
