#ifndef EXPENSETRANSACTION_H
#define EXPENSETRANSACTION_H

#include "basetransaction.h"

struct ExpenseTransaction : public BaseTransaction
{
    std::string type = "";
    std::string description = "";
};

#endif // EXPENSETRANSACTION_H
