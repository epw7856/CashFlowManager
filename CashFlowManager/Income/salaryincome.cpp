#include "salaryincome.h"

SalaryIncome::SalaryIncome
(
    const QDate& inputDate
)
:
    BaseTransaction(inputDate, 0.0)
{

}

SalaryIncome::SalaryIncome
(
    const QDate& inputDate,
    double inputAmount,
    unsigned inputOvertime
)
:
    BaseTransaction(inputDate, inputAmount),
    overtime(inputOvertime)
{

}

unsigned SalaryIncome::getOvertime() const
{
    return overtime;
}
