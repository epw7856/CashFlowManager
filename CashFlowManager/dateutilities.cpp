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

std::pair<QDate, QDate> DateUtilities::getMonthlyDates(int month)
{
    QDate startDate(QDate::currentDate().year(), month, 1);
    QDate endDate(QDate::currentDate().year(), month, startDate.daysInMonth());
    return {startDate, endDate};
}
