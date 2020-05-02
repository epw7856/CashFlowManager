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

inline std::string ExpenseTransaction::getDescription() const
{
    return description;
}

#endif // EXPENSETRANSACTION_H
