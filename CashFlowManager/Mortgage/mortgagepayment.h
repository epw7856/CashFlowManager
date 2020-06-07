#ifndef MORTGAGEPAYMENT_H
#define MORTGAGEPAYMENT_H

#include "basetransaction.h"

class MortgagePayment : public BaseTransaction
{
public:
    MortgagePayment(const QDate& inputDate);
    MortgagePayment(const QDate& inputDate, double inputAmount, double inputAdditionalPrincipal);
    double getAdditionalPrincipalPayment() const;

private:
    double additionalPrincipalPayment = 0.0;
};

inline double MortgagePayment::getAdditionalPrincipalPayment() const
{
    return additionalPrincipalPayment;
}

#endif // MORTGAGEPAYMENT_H
