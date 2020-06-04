#ifndef CURRENCYUTILITIES_H
#define CURRENCYUTILITIES_H

#include <string>

class CurrencyUtilities
{
public:
    CurrencyUtilities() {}
    static std::string formatCurrency(int amount);
    static std::string formatCurrency(double amount);
    static std::string formatRatio(double amount);
    static double formatCurrencyToDouble(const std::string& amount);
    static double formatRatioToDouble(const std::string& ratio);
};

#endif // CURRENCYUTILITIES_H
