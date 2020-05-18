#ifndef INVESTMENTINTERFACE_H
#define INVESTMENTINTERFACE_H

#include <set>
#include <string>
#include <vector>

class QDate;
class InvestmentType;
class InvestmentTransaction;

class InvestmentInterface
{
public:
    virtual ~InvestmentInterface() = default;
    virtual std::vector<InvestmentType*> getInvestmentTypes() const = 0;
    virtual std::vector<InvestmentTransaction*> getInvestmentTransactionsByTimePeriod(const std::string& investmentType, const QDate& startingPeriod, const QDate& endingPeriod) const = 0;
    virtual double getInvestmentTransactionsTotalByTimePeriod(const std::string& investmentType, const QDate& startingPeriod, const QDate& endingPeriod) const = 0;
    virtual void addInvestmentType(const InvestmentType& type) = 0;
    virtual void addInvestmentTransactionByType(const std::string& investmentType, const InvestmentTransaction& transaction) = 0;
    virtual double getMonthlyInvestmentTotal(int month) const = 0;
    virtual double getYearlyInvestmentTotal() const = 0;
    virtual double getMonthlyInvestmentTotalByType(const std::string& investmentType) const = 0;
    virtual double getYearlyInvestmentTotalByType(const std::string& investmentType) const = 0;
    virtual double getMonthlyInvestmentTargetTotal() const = 0;
};

#endif // INVESTMENTINTERFACE_H
