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

std::string InvestmentType::getName() const
{
    return name;
}

double InvestmentType::getMonthlyTarget() const
{
    return monthlyTarget;
}

void InvestmentType::addInvestmentTransaction(const InvestmentTransaction& transaction)
{
    investmentTransactionList.insert(std::make_unique<InvestmentTransaction>(transaction));
}

const std::multiset<std::unique_ptr<InvestmentTransaction>, TransactionComparison<InvestmentTransaction>>& InvestmentType::getTransactionList() const
{
    return investmentTransactionList;
}
