#ifndef INVESTMENTTRANSACTION_H
#define INVESTMENTTRANSACTION_H

#include "basetransaction.h"

class InvestmentTransaction : public BaseTransaction
{
public:
    InvestmentTransaction(QDate inputDate, double inputAmount, std::string inputType);

    std::string getType() const;

private:
    std::string type = "";
};

#endif // INVESTMENTTRANSACTION_H
