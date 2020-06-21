#ifndef INVESTMENTTYPE_H
#define INVESTMENTTYPE_H

#include <set>
#include <string>
#include "transactioncomparison.h"

class InvestmentTransaction;
class QDate;

class InvestmentType
{
public:
    InvestmentType(std::string inputName, double inputTarget);
    void updateName(const std::string& updatedName);
    void updateBudget(double updatedAmount);
    std::string getName() const;
    double getMonthlyTarget() const;
    void addInvestmentTransaction(const InvestmentTransaction& transaction);
    const std::multiset<std::unique_ptr<InvestmentTransaction>, TransactionComparison<InvestmentTransaction>>& getTransactionList() const;

private:
    std::string name = "";
    double monthlyTarget = 0.00;
    std::multiset<std::unique_ptr<InvestmentTransaction>, TransactionComparison<InvestmentTransaction>> investmentTransactionList;
};

inline void InvestmentType::updateName(const std::string& updatedName)
{
    name = updatedName;
}

inline void InvestmentType::updateBudget(double updatedAmount)
{
    monthlyTarget = updatedAmount;
}

inline std::string InvestmentType::getName() const
{
    return name;
}

inline double InvestmentType::getMonthlyTarget() const
{
    return monthlyTarget;
}

#endif // INVESTMENTTYPE_H
