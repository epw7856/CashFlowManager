#ifndef SUPPLEMENTALINCOME_H
#define SUPPLEMENTALINCOME_H

#include "basetransaction.h"

class SupplementalIncome : public BaseTransaction
{
public:
    SupplementalIncome(QDate inputDate, double inputAmount, std::string inputDescription);

    std::string getDescription() const;

private:
    std::string description = "";
};

#endif // SUPPLEMENTALINCOME_H
