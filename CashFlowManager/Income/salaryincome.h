#ifndef SALARYINCOME_H
#define SALARYINCOME_H

#include "basetransaction.h"

class SalaryIncome : public BaseTransaction
{
public:
    SalaryIncome
    (
        QDate inputDate,
        double inputAmount,
        unsigned inputOvertime
    )
    :
        BaseTransaction(inputDate, inputAmount),
        overtime(inputOvertime){}

    unsigned getOvertime() const;

private:
    unsigned overtime = 0U;
};

#endif // SALARYINCOME_H

unsigned SalaryIncome::getOvertime() const
{
    return overtime;
}
