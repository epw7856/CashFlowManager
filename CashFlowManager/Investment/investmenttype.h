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
    std::string getName() const;
    double getMonthlyTarget() const;
    void addInvestmentTransaction(const InvestmentTransaction& transaction);
    const std::multiset<std::unique_ptr<InvestmentTransaction>, TransactionComparison<InvestmentTransaction>>& getTransactionList() const;

private:
    std::string name = "";
    double monthlyTarget = 0.00;
    std::multiset<std::unique_ptr<InvestmentTransaction>, TransactionComparison<InvestmentTransaction>> investmentTransactionList;
};

#endif // INVESTMENTTYPE_H
