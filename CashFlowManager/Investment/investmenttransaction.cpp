#include "investmenttransaction.h"

InvestmentTransaction::InvestmentTransaction
(
    QDate inputDate,
    double inputAmount,
    std::string inputType
)
:
    BaseTransaction(inputDate, inputAmount),
    type(inputType)
{

}

std::string InvestmentTransaction::getType() const
{
    return type;
}
