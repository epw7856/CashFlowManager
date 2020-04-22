#ifndef SUPPLEMENTALINCOME_H
#define SUPPLEMENTALINCOME_H

#include "basetransaction.h"

struct SupplementalIncome : public BaseTransaction
{
    std::string Description = "";
};

#endif // SUPPLEMENTALINCOME_H
