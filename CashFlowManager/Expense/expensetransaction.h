#ifndef EXPENSETRANSACTION_H
#define EXPENSETRANSACTION_H

#include "basetransaction.h"

class ExpenseTransaction : public BaseTransaction
{
public:
    ExpenseTransaction(const QDate& inputDate);
    ExpenseTransaction(const QDate& inputDate, double inputAmount, const std::string& inputDescription);
    std::string getDescription() const;

private:
    std::string description = "";
};

#endif // EXPENSETRANSACTION_H
