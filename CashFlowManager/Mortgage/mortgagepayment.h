#ifndef MORTGAGEPAYMENT_H
#define MORTGAGEPAYMENT_H

#include "basetransaction.h"

class MortgagePayment : public BaseTransaction
{
public:
    MortgagePayment(const QDate& inputDate);
    MortgagePayment(const QDate& inputDate, double inputAmount, double inputAdditionalPrincipal);

private:
    double additionalPrincipalPayment = 0.0;
};

#endif // MORTGAGEPAYMENT_H
