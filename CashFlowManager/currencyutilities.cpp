#include "currencyutilities.h"
#include <QLocale>

std::string CurrencyUtilities::formatCurrency(double amount, bool trimPrecision)
{
    std::string value;
    value = "$" + QLocale(QLocale::English).toString(amount, 'f', 2).toStdString();
    if(amount < 0.0)
    {
        amount *= -1.0;
        value.insert(0, "-");
    }

    if(trimPrecision)
    {
        value.erase(value.size() - 3);
    }

    return value;
}

std::string CurrencyUtilities::formatRatio(double ratio, int precision)
{
    return QLocale(QLocale::English).toString(ratio * 100.0, 'f', precision).toStdString() + "%";
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
    return (negative) ? (-1.0) * convertedValue : convertedValue;
}

double CurrencyUtilities::formatRatioToDouble(const std::string& ratio)
{
    double convertedValue = 0.0;
    QString interRatio = QString::fromStdString(ratio);
    bool negative = false;

    if(interRatio == "N/A")
    {
        return convertedValue;
    }

    interRatio.remove(interRatio.size() - 1, 1);

    if(interRatio.at(0) == '-')
    {
        negative = true;
        interRatio.remove(0, 1);
    }

    convertedValue = interRatio.toDouble() / 100.0;
    return (negative) ? (-1.0) * convertedValue : convertedValue;
}
