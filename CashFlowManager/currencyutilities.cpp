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

std::string CurrencyUtilities::formatRatio(double amount)
{
    return QLocale(QLocale::English).toString(amount*100, 'f', 2).toStdString() + "%";
}

double CurrencyUtilities::formatCurrencyToDouble(const std::string& amount)
{
    double convertedValue = 0.0;
    QString interAmount = QString::fromStdString(amount);
    bool negative = false;
    if(interAmount.at(0) == '-')
    {
        negative = true;
        interAmount.remove(0, 2);
    }
    else
    {
        interAmount.remove(0, 1);
    }
    interAmount.remove(',');
    convertedValue = interAmount.toDouble();
    return (negative) ? (-1.0)*convertedValue : convertedValue;
}
