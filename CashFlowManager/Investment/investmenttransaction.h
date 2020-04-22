#ifndef INVESTMENTTRANSACTION_H
#define INVESTMENTTRANSACTION_H

#include "basetransaction.h"

struct InvestmentTransaction : public BaseTransaction
{
    std::string type = "";
};

#endif // INVESTMENTTRANSACTION_H
