#ifndef BASETRANSACTION_H
#define BASETRANSACTION_H

#include <QDate>

struct BaseTransaction
{
    QDate date;
    double amount = 0.0;

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
};

#endif // BASETRANSACTION_H
