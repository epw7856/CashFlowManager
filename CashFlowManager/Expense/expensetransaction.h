#ifndef EXPENSETRANSACTION_H
#define EXPENSETRANSACTION_H

#include "basetransaction.h"

struct ExpenseTransaction : public BaseTransaction
{
    std::string Type = "";
    std::string Description = "";
};

#endif // EXPENSETRANSACTION_H
