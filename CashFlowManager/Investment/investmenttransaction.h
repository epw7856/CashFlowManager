#ifndef INVESTMENTTRANSACTION_H
#define INVESTMENTTRANSACTION_H

#include "basetransaction.h"

struct InvestmentTransaction : public BaseTransaction
{
    std::string Type = "";
};

#endif // INVESTMENTTRANSACTION_H
