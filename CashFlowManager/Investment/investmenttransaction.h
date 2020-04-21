#ifndef INVESTMENTTRANSACTION_H
#define INVESTMENTTRANSACTION_H

#include <QDate>

struct InvestmentTransaction
{
    std::string type = "";
    QDate date;
    double amount = 0.0;

    friend bool operator<(const InvestmentTransaction& lhs, const InvestmentTransaction& rhs)
    {
        return lhs.date < rhs.date;
    }

    friend bool operator<=(const InvestmentTransaction& lhs, const InvestmentTransaction& rhs)
    {
        return lhs.date <= rhs.date;
    }

    friend bool operator>(const InvestmentTransaction& lhs, const InvestmentTransaction& rhs)
    {
        return lhs.date > rhs.date;
    }

    friend bool operator>=(const InvestmentTransaction& lhs, const InvestmentTransaction& rhs)
    {
        return lhs.date >= rhs.date;
    }
};

#endif // INVESTMENTTRANSACTION_H
