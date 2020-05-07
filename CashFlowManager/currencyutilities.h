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
};

#endif // CURRENCYUTILITIES_H