#include "salaryincome.h"

SalaryIncome::SalaryIncome
(
    QDate inputDate,
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
