#ifndef INVESTMENTTRANSACTION_H
#define INVESTMENTTRANSACTION_H

#include "basetransaction.h"

class InvestmentTransaction : public BaseTransaction
{
public:
    InvestmentTransaction(const QDate& inputDate);
    InvestmentTransaction(const QDate& inputDate, double inputAmount);
};

#endif // INVESTMENTTRANSACTION_H
