#ifndef MORTGAGEPAYMENT_H
#define MORTGAGEPAYMENT_H

#include "basetransaction.h"

struct MortgagePayment : public BaseTransaction
{
    double AdditionalPrincipalPayment = 0.0;
};

#endif // MORTGAGEPAYMENT_H
