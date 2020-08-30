#ifndef DATEUTILITIES_H
#define DATEUTILITIES_H

#include <QDate>
#include <string>

class DateUtilities
{
public:
    DateUtilities() {}
    static std::pair<QDate, QDate> getCurrentMonthDates();
    static std::pair<QDate, QDate> getCurrentYearDates();
    static std::pair<QDate, QDate> getMonthlyDates(int year, int month);
    static std::pair<QDate, QDate> getYearlyDates(int year);
};

#endif // DATEUTILITIES_H
