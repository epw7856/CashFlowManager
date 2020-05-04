#ifndef DATEUTILITIES_H
#define DATEUTILITIES_H

#include <QDate>
#include <string>

class DateUtilities
{
public:
    DateUtilities() {}
    static std::string getCurrentMonth();
    static std::string getCurrentYear();
    static std::pair<QDate, QDate> getCurrentMonthDates();
    static std::pair<QDate, QDate> getCurrentYearDates();
    static std::pair<QDate, QDate> getMonthlyDates(int month);
};

#endif // DATEUTILITIES_H
