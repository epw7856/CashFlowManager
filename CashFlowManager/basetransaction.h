#ifndef BASETRANSACTION_H
#define BASETRANSACTION_H

#include <QDate>

struct BaseTransaction
{
    QDate Date;
    double Amount = 0.0;

    friend bool operator<(const BaseTransaction& lhs, const BaseTransaction& rhs)
    {
        return lhs.Date < rhs.Date;
    }

    friend bool operator<=(const BaseTransaction& lhs, const BaseTransaction& rhs)
    {
        return lhs.Date <= rhs.Date;
    }

    friend bool operator>(const BaseTransaction& lhs, const BaseTransaction& rhs)
    {
        return lhs.Date > rhs.Date;
    }

    friend bool operator>=(const BaseTransaction& lhs, const BaseTransaction& rhs)
    {
        return lhs.Date >= rhs.Date;
    }
};

#endif // BASETRANSACTION_H
