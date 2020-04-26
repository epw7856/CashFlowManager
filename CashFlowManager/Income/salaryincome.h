#ifndef SALARYINCOME_H
#define SALARYINCOME_H

#include "basetransaction.h"

class SalaryIncome : public BaseTransaction
{
public:
    SalaryIncome(QDate inputDate, double inputAmount, unsigned inputOvertime);

    unsigned getOvertime() const;

private:
    unsigned overtime = 0U;
};

#endif // SALARYINCOME_H
