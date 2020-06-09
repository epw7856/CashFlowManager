#ifndef MORTGAGEPRINCIPALPAYMENT_H
#define MORTGAGEPRINCIPALPAYMENT_H

#include "basetransaction.h"

class MortgagePrincipalPayment : public BaseTransaction
{
public:
    MortgagePrincipalPayment(const QDate& inputDate);
    MortgagePrincipalPayment(const QDate& inputDate, double inputAmount);
};

#endif // MORTGAGEPRINCIPALPAYMENT_H
