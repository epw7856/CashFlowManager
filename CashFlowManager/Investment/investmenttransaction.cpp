#include "investmenttransaction.h"

InvestmentTransaction::InvestmentTransaction(const QDate& inputDate)
:
    BaseTransaction(inputDate, 0.0)
{

}

InvestmentTransaction::InvestmentTransaction
(
    const QDate& inputDate,
    double inputAmount
)
:
    BaseTransaction(inputDate, inputAmount)
{

}
