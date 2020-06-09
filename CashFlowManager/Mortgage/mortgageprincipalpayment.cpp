#include "mortgageprincipalpayment.h"

MortgagePrincipalPayment::MortgagePrincipalPayment
(
    const QDate& inputDate
)
:
    BaseTransaction(inputDate, 0.0)
{

}

MortgagePrincipalPayment::MortgagePrincipalPayment
(
    const QDate& inputDate,
    double inputAmount
)
:
    BaseTransaction(inputDate, inputAmount)
{

}

