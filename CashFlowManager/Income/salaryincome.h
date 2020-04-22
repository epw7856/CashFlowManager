#ifndef SALARYINCOME_H
#define SALARYINCOME_H

#include "basetransaction.h"

struct SalaryIncome : public BaseTransaction
{
    unsigned Overtime = 0U;
};

#endif // SALARYINCOME_H
