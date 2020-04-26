#ifndef INCOMEINTERFACE_H
#define INCOMEINTERFACE_H

#include <set>

class QDate;
class SalaryIncome;
class SupplementalIncome;

class IncomeInterface
{
public:
    virtual ~IncomeInterface() = default;
    virtual std::multiset<SalaryIncome*> getSalaryIncomeTransactionsByTimePeriod(QDate startingPeriod, QDate endingPeriod) const = 0;
    virtual std::multiset<SupplementalIncome*> getSupplementalIncomeTransactionsByTimePeriod(QDate startingPeriod, QDate endingPeriod) const = 0;
    virtual double getTotalIncomeByTimePeriod(QDate startingPeriod, QDate endingPeriod) const = 0;
    virtual double getSalaryIncomeByTimePeriod(QDate startingPeriod, QDate endingPeriod) const = 0;
    virtual void addSalaryPayment(const SalaryIncome& payment) = 0;
    virtual void addSupplementalPayment(const SupplementalIncome& payment) = 0;

};

#endif // INCOMEINTERFACE_H
