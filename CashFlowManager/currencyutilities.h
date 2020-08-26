#ifndef CURRENCYUTILITIES_H
#define CURRENCYUTILITIES_H

#include <string>

class CurrencyUtilities
{
public:
    CurrencyUtilities() {}
    static std::string formatCurrency(double amount, bool trimPrecision = false);
    static std::string formatRatio(double ratio, int precision = 2);
    static std::string formatDouble(double amount);
    static double formatCurrencyToDouble(const std::string& amount);
    static double formatRatioToDouble(const std::string& ratio);
};

#endif // CURRENCYUTILITIES_H
