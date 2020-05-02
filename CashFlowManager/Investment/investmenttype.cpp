#include "investmenttransaction.h"
#include "investmenttype.h"

InvestmentType::InvestmentType
(
    std::string inputName,
    double inputTarget
)
:
    name(inputName),
    monthlyTarget(inputTarget)
{

}

void InvestmentType::addInvestmentTransaction(const InvestmentTransaction& transaction)
{
    investmentTransactionList.insert(std::make_unique<InvestmentTransaction>(transaction));
}

const std::multiset<std::unique_ptr<InvestmentTransaction>, TransactionComparison<InvestmentTransaction>>& InvestmentType::getTransactionList() const
{
    return investmentTransactionList;
}
