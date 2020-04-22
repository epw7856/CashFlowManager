#ifndef INCOMEINTERFACE_H
#define INCOMEINTERFACE_H

#include <QDate>

class IncomeInterface
{
    virtual double getTotalIncomeByTimePeriod(QDate startingPeriod, QDate endingPeriod) const = 0;
    virtual double getSalaryIncomeByTimePeriod(QDate startingPeriod, QDate endingPeriod) const = 0;
};

#endif // INCOMEINTERFACE_H
