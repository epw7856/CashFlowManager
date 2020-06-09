#include "dateutilities.h"

std::string DateUtilities::getCurrentMonth()
{
    QDate date(QDate::currentDate());
    return date.toString("MMMM").toStdString();
}

std::string DateUtilities::getCurrentYear()
{
    QDate date(QDate::currentDate());
    return date.toString("yyyy").toStdString();
}

std::pair<QDate, QDate> DateUtilities::getCurrentMonthDates()
{
    QDate startDate(QDate::currentDate().year(), QDate::currentDate().month(), 1);
    QDate endDate(QDate::currentDate().year(), QDate::currentDate().month(), QDate::currentDate().daysInMonth());
    return {startDate, endDate};
}

std::pair<QDate, QDate> DateUtilities::getCurrentYearDates()
{
    QDate startDate(QDate::currentDate().year(), 1, 1);
    QDate endDate(QDate::currentDate().year(), 12, 31);
    return {startDate, endDate};
}

std::pair<QDate, QDate> DateUtilities::getMonthlyDates(int year, int month)
{
    QDate startDate(year, month, 1);
    QDate endDate(year, month, startDate.daysInMonth());
    return {startDate, endDate};
}

std::pair<QDate, QDate> DateUtilities::getYearlyDates(int year)
{
    QDate startDate(year, 1, 1);
    QDate endDate(year, 12, 31);
    return {startDate, endDate};
}
