#include "currencyutilities.h"
#include <QLocale>

std::string CurrencyUtilities::formatCurrency(int amount)
{
    return "$" + QLocale(QLocale::English).toString(static_cast<double>(amount), 'f', 2).toStdString();
}

std::string CurrencyUtilities::formatCurrency(double amount)
{
    return "$" + QLocale(QLocale::English).toString(amount, 'f', 2).toStdString();
}
