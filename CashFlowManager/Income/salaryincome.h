#ifndef SALARYINCOME_H
#define SALARYINCOME_H

#include "basetransaction.h"

class SalaryIncome : public BaseTransaction
{
public:
    SalaryIncome(const QDate& inputDate);
    SalaryIncome(const QDate& inputDate, double inputAmount, unsigned inputOvertime);
    unsigned getOvertime() const;

private:
    unsigned overtime = 0U;
};

inline unsigned SalaryIncome::getOvertime() const
{
    return overtime;
}

#endif // SALARYINCOME_H
