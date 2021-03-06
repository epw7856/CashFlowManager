#ifndef INCOMEINTERFACE_H
#define INCOMEINTERFACE_H

#include <set>
#include <vector>

class QDate;
class SalaryIncome;
class SupplementalIncome;

class IncomeInterface
{
public:
    virtual ~IncomeInterface() = default;
    virtual std::vector<SalaryIncome*> getSalaryIncomeTransactionsByTimePeriod(const QDate& startingPeriod, const QDate& endingPeriod) const = 0;
    virtual std::vector<SupplementalIncome*> getSupplementalIncomeTransactionsByTimePeriod(const QDate& startingPeriod, const QDate& endingPeriod) const = 0;
    virtual double getTotalIncomeTotalByTimePeriod(const QDate& startingPeriod, const QDate& endingPeriod) const = 0;
    virtual double getSalaryIncomeTotalByTimePeriod(const QDate& startingPeriod, const QDate& endingPeriod) const = 0;
    virtual double getSupplementalIncomeTotalByTimePeriod(const QDate& startingPeriod, const QDate& endingPeriod) const = 0;
    virtual void addSalaryPayment(const SalaryIncome& payment) = 0;
    virtual void addSupplementalPayment(const SupplementalIncome& payment) = 0;
    virtual double getMonthlyIncomeTotal(int year, int month) const = 0;
    virtual double getYearlyIncomeTotal(int year) const = 0;
    virtual int getYearlyOvertimeTotal() const = 0;

};

#endif // INCOMEINTERFACE_H
