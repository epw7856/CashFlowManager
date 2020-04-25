#ifndef BASETRANSACTION_H
#define BASETRANSACTION_H

#include <QDate>

class BaseTransaction
{
public:

    BaseTransaction(QDate inputDate, double inputAmount);

    QDate getDate() const;

    double getAmount() const;

    friend bool operator<(const BaseTransaction& lhs, const BaseTransaction& rhs)
    {
        return lhs.date < rhs.date;
    }

    friend bool operator<=(const BaseTransaction& lhs, const BaseTransaction& rhs)
    {
        return lhs.date <= rhs.date;
    }

    friend bool operator>(const BaseTransaction& lhs, const BaseTransaction& rhs)
    {
        return lhs.date > rhs.date;
    }

    friend bool operator>=(const BaseTransaction& lhs, const BaseTransaction& rhs)
    {
        return lhs.date >= rhs.date;
    }

private:
    QDate date;
    double amount = 0.0;
};

#endif // BASETRANSACTION_H
