#include "basetransaction.h"

BaseTransaction::BaseTransaction(QDate inputDate, double inputAmount)
:
    date(inputDate),
    amount(inputAmount)
{

}

QDate BaseTransaction::getDate() const
{
return date;
}

double BaseTransaction::getAmount() const
{
return amount;
}
