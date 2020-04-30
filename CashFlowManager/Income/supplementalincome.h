#ifndef SUPPLEMENTALINCOME_H
#define SUPPLEMENTALINCOME_H

#include "basetransaction.h"

class SupplementalIncome : public BaseTransaction
{
public:
    SupplementalIncome(const QDate& inputDate);
    SupplementalIncome(const QDate& inputDate, double inputAmount, const std::string& inputDescription);
    std::string getDescription() const;

private:
    std::string description = "";
};

#endif // SUPPLEMENTALINCOME_H
