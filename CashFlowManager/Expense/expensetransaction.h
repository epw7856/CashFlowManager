#ifndef EXPENSETRANSACTION_H
#define EXPENSETRANSACTION_H

#include "basetransaction.h"

class ExpenseTransaction : public BaseTransaction
{
public:
    ExpenseTransaction
    (
        QDate inputDate,
        double inputAmount,
        std::string inputType,
        std::string inputDescription
    )
    :
        BaseTransaction(inputDate, inputAmount),
        type(inputType),
        description(inputDescription){}

    std::string getType() const;

    std::string getDescription() const;

private:
    std::string type = "";
    std::string description = "";
};

#endif // EXPENSETRANSACTION_H

std::string ExpenseTransaction::getType() const
{
    return type;
}

std::string ExpenseTransaction::getDescription() const
{
    return description;
}
