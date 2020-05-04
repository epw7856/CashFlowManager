#include "currencyutilities.h"
#include <QLocale>

std::string CurrencyUtilities::formatCurrency(int amount)
{
    if(amount < 0)
    {
        amount *= -1;
        return "-$" + QLocale(QLocale::English).toString(static_cast<double>(amount), 'f', 2).toStdString();
    }
    return "$" + QLocale(QLocale::English).toString(static_cast<double>(amount), 'f', 2).toStdString();
}

std::string CurrencyUtilities::formatCurrency(double amount)
{
    if(amount < 0.0)
    {
        amount *= -1.0;
        return "-$" + QLocale(QLocale::English).toString(amount, 'f', 2).toStdString();
    }
    return "$" + QLocale(QLocale::English).toString(amount, 'f', 2).toStdString();
}
