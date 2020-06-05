#include "mortgagepayment.h"

MortgagePayment::MortgagePayment
(
    const QDate& inputDate
)
:
    BaseTransaction(inputDate, 0.0)
{

}

MortgagePayment::MortgagePayment
(
    const QDate& inputDate,
    double inputAmount,
    double inputAdditionalPrincipal
)
:
    BaseTransaction(inputDate, inputAmount),
    additionalPrincipalPayment(inputAdditionalPrincipal)
{

}

