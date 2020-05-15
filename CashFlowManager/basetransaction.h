#ifndef BASETRANSACTION_H
#define BASETRANSACTION_H

#include <QDate>

class BaseTransaction
{
public:
    BaseTransaction(QDate inputDate, double inputAmount);
    QDate getDate() const;
    double getAmount() const;

private:
    QDate date;
    double amount = 0.0;
};

#endif // BASETRANSACTION_H
