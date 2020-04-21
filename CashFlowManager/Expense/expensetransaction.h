#ifndef EXPENSETRANSACTION_H
#define EXPENSETRANSACTION_H

#include <QDate>

struct ExpenseTransaction
{
    std::string type = "";
    std::string description = "";
    QDate date;
    double amount = 0.0;

    friend bool operator<(const ExpenseTransaction& lhs, const ExpenseTransaction& rhs)
    {
        return lhs.date < rhs.date;
    }

    friend bool operator<=(const ExpenseTransaction& lhs, const ExpenseTransaction& rhs)
    {
        return lhs.date <= rhs.date;
    }

    friend bool operator>(const ExpenseTransaction& lhs, const ExpenseTransaction& rhs)
    {
        return lhs.date > rhs.date;
    }

    friend bool operator>=(const ExpenseTransaction& lhs, const ExpenseTransaction& rhs)
    {
        return lhs.date >= rhs.date;
    }
};

#endif // EXPENSETRANSACTION_H
