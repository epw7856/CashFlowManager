#include "assetentry.h"
#include "automaticmonthlypayment.h"
#include "dateutilities.h"
#include "expensetransaction.h"
#include "expensetype.h"
#include "investmenttransaction.h"
#include "investmenttype.h"
#include "mortgageinformation.h"
#include <QByteArray>
#include <QDebug>
#include <QJsonArray>
#include <QJsonDocument>
#include "salaryincome.h"
#include "supplementalincome.h"
#include "systemdatasource.h"

SystemDataSource::SystemDataSource(const std::string& filePath)
:
    systemConfigFile(QString::fromStdString(filePath))
{
    loadSystemConfig();
}

SystemDataSource::~SystemDataSource() = default;

bool SystemDataSource::loadSystemConfig()
{
    if(!systemConfigFile.open((QIODevice::ReadOnly | QIODevice::Text)))
    {
        qWarning() << "Unable to load System Configuration.";
        createSystemConfigurationTemplate();
        return false;
    }

    QByteArray rawData = systemConfigFile.readAll();
    systemConfigFile.close();
    QJsonDocument doc = QJsonDocument::fromJson(rawData);
    obj = doc.object();

    parseExpenseTypes();
    parseInvestmentTypes();
    parseAutomaticMonthlyPayments();
    parseSalaryIncome();
    parseSupplementalIncome();
    parseAssetList();

    return true;
}

bool SystemDataSource::saveSystemConfig()
{
    if (!systemConfigFile.open(QIODevice::WriteOnly))
    {
        qWarning("Unable to save System Configuration.");
        return false;
    }

    QJsonDocument doc(obj);
    systemConfigFile.write(doc.toJson());
    systemConfigFile.close();

    return true;
}

void SystemDataSource::createSystemConfigurationTemplate()
{
    systemConfigFile.setFileName("../SystemConfiguration.json");
    if(!systemConfigFile.open(QIODevice::WriteOnly))
    {
        qWarning() << "Unable to create new System Configuration.";
        return;
    }
    systemConfigFile.close();

    QJsonValue empty;

    obj.insert("Assets", empty);
    obj.insert("AutomaticMonthlyPayments", empty);
    obj.insert("ExpenseTypes", empty);
    obj.insert("InvestmentTypes", empty);
    obj.insert("Investments", empty);
    obj.insert("MortgageInformation", empty);
    obj.insert("SalaryIncome", empty);
    obj.insert("SupplementalIncome", empty);
}

std::vector<ExpenseType*> SystemDataSource::getExpenseTypes() const
{
    std::vector<ExpenseType*> types;
    types.reserve(expenseTypes.size());

    for(auto i = expenseTypes.begin(); i != expenseTypes.end(); ++i)
    {
        types.push_back(i->get());
    }

    return types;
}

std::multiset<ExpenseTransaction*> SystemDataSource::getExpenseTransactionsByTimePeriod(const std::string& expenseType,
                                                                                        const QDate& startingPeriod,
                                                                                        const QDate& endingPeriod) const
{
    auto itr = findMatchingType(expenseTypes, expenseType);

    if(itr != expenseTypes.end())
    {
        return getTransactionsByTimePeriod(itr->get()->getTransactionList(), startingPeriod, endingPeriod);
    }

    return {};
}

double SystemDataSource::getExpenseTransactionsTotalByTimePeriod(const std::string &expenseType,
                                                                 const QDate& startingPeriod,
                                                                 const QDate& endingPeriod) const
{
    auto itr = findMatchingType(expenseTypes, expenseType);

    if(itr != expenseTypes.end())
    {
        return getTransactionsTotalByTimePeriod(itr->get()->getTransactionList(), startingPeriod, endingPeriod);
    }
    return 0.0;
}

std::vector<AutomaticMonthlyPayment*> SystemDataSource::getAutomaticMonthlyPayments() const
{
    std::vector<AutomaticMonthlyPayment*> payments;
    payments.reserve(automaticMonthlyPaymentList.size());

    for(auto i = automaticMonthlyPaymentList.begin(); i != automaticMonthlyPaymentList.end(); ++i)
    {
        payments.push_back(i->get());
    }

    return payments;
}

void SystemDataSource::addExpenseType(const ExpenseType& type)
{
    expenseTypes.push_back(std::make_unique<ExpenseType>(type.getName(), type.getMonthlyBudget()));

    QJsonArray array = obj.value("ExpenseTypes").toArray();
    QJsonObject item;
    item.insert("MonthlyBudget", QJsonValue(type.getMonthlyBudget()));
    item.insert("Name", QJsonValue(QString::fromStdString(type.getName())));
    item.insert("Transactions", QJsonArray());
    array.append(item);
    obj["ExpenseTypes"] = array;

}

void SystemDataSource::addExpenseTransactionByType(const std::string& expenseType, const ExpenseTransaction& transaction)
{
    ExpenseTransaction newTransaction(transaction.getDate(),
                                      transaction.getAmount(),
                                      transaction.getDescription());

    auto itr = findMatchingType(expenseTypes, expenseType);

    if(itr != expenseTypes.end())
    {
        itr->get()->addExpenseTransaction(newTransaction);

        QJsonArray array = obj.value("ExpenseTypes").toArray();
        for(int i = 0; i < array.size(); ++i)
        {
            QJsonObject item = array.at(i).toObject();
            if(QString(item.value("Name").toString()).toStdString() == expenseType)
            {
                QJsonArray values = item.value("Transactions").toArray();

                QJsonObject newValueItem;
                newValueItem.insert("Date", QJsonValue(transaction.getDate().toString("MM/dd/yyyy")));
                newValueItem.insert("Amount", QJsonValue(transaction.getAmount()));
                newValueItem.insert("Description", QJsonValue(QString::fromStdString(transaction.getDescription())));
                values.append(newValueItem);
                item.remove("Transactions");
                item.insert("Transactions", values);
                array.removeAt(i);
                array.insert(i,item);
            }
        }
        obj["ExpenseTypes"] = array;
    }
}

void SystemDataSource::addAutomaticMonthlyPayment(const AutomaticMonthlyPayment& payment)
{
    automaticMonthlyPaymentList.push_back(std::make_unique<AutomaticMonthlyPayment>(payment.getName(),
                                                                                    payment.getAccount(),
                                                                                    payment.getAmount()));

    QJsonArray array = obj.value("AutomaticMonthlyPayments").toArray();
    QJsonObject item;
    item.insert("Account", QJsonValue(QString::fromStdString(payment.getAccount())));
    item.insert("Amount", QJsonValue(payment.getAmount()));
    item.insert("Name", QJsonValue(QString::fromStdString(payment.getName())));
    array.append(item);
    obj["AutomaticMonthlyPayments"] = array;
}

double SystemDataSource::getMonthlyExpenses() const
{
    double total = 0.0;
    std::pair<QDate, QDate> dates = DateUtilities::getCurrentMonthDates();
    for(const auto& i : expenseTypes)
    {
        total += getExpenseTransactionsTotalByTimePeriod(i->getName(), dates.first, dates.second);
    }
    return total;
}

double SystemDataSource::getMonthlyBudget() const
{
    double total = 0.0;
    for(const auto& i : expenseTypes)
    {
        total += i->getMonthlyBudget();
    }
    return total;
}

double SystemDataSource::getYearlyExpenses() const
{
    double total = 0.0;
    std::pair<QDate, QDate> dates = DateUtilities::getCurrentYearDates();
    for(const auto& i : expenseTypes)
    {
        total += getExpenseTransactionsTotalByTimePeriod(i->getName(), dates.first, dates.second);
    }
    return total;
}

std::vector<InvestmentType*> SystemDataSource::getInvestmentTypes() const
{
    std::vector<InvestmentType*> types;
    types.reserve(investmentTypes.size());

    for(auto i = investmentTypes.begin(); i != investmentTypes.end(); ++i)
    {
        types.push_back(i->get());
    }

    return types;
}

std::multiset<InvestmentTransaction*> SystemDataSource::getInvestmentTransactionsByTimePeriod(const std::string& investmentType,
                                                                                              const QDate& startingPeriod,
                                                                                              const QDate& endingPeriod) const
{
    auto itr = findMatchingType(investmentTypes, investmentType);

    if(itr != investmentTypes.end())
    {
        return getTransactionsByTimePeriod(itr->get()->getTransactionList(), startingPeriod, endingPeriod);;
    }

    return {};
}

double SystemDataSource::getInvestmentTransactionsTotalByTimePeriod(const std::string& investmentType,
                                                                    const QDate& startingPeriod,
                                                                    const QDate& endingPeriod) const
{
    auto itr = findMatchingType(investmentTypes, investmentType);

    if(itr != investmentTypes.end())
    {
        return getTransactionsTotalByTimePeriod(itr->get()->getTransactionList(), startingPeriod, endingPeriod);
    }
    return 0.0;
}

void SystemDataSource::addInvestmentType(const InvestmentType& type)
{
    investmentTypes.push_back(std::make_unique<InvestmentType>(type.getName(), type.getMonthlyTarget()));

    QJsonArray array = obj.value("InvestmentTypes").toArray();
    QJsonObject item;
    item.insert("MonthlyTarget", QJsonValue(type.getMonthlyTarget()));
    item.insert("Name", QJsonValue(QString::fromStdString(type.getName())));
    item.insert("Transactions", QJsonArray());
    array.append(item);
    obj["InvestmentTypes"] = array;
}

void SystemDataSource::addInvestmentTransactionByType(const std::string& investmentType, const InvestmentTransaction& transaction)
{
    InvestmentTransaction newTransaction(transaction.getDate(),
                                         transaction.getAmount());

    auto itr = findMatchingType(investmentTypes, investmentType);

    if(itr != investmentTypes.end())
    {
        itr->get()->addInvestmentTransaction(newTransaction);

        QJsonArray array = obj.value("InvestmentTypes").toArray();
        for(int i = 0; i < array.size(); ++i)
        {
            QJsonObject item = array.at(i).toObject();
            if(QString(item.value("Name").toString()).toStdString() == investmentType)
            {
                QJsonArray values = item.value("Transactions").toArray();

                QJsonObject newValueItem;
                newValueItem.insert("Date", QJsonValue(transaction.getDate().toString("MM/dd/yyyy")));
                newValueItem.insert("Amount", QJsonValue(transaction.getAmount()));
                values.append(newValueItem);
                item.remove("Transactions");
                item.insert("Transactions", values);
                array.removeAt(i);
                array.insert(i,item);
            }
        }
        obj["InvestmentTypes"] = array;
    }
}

double SystemDataSource::getMonthlyInvestments() const
{
    double total = 0.0;
    std::pair<QDate, QDate> dates = DateUtilities::getCurrentMonthDates();
    for(const auto& i : investmentTypes)
    {
        total += getInvestmentTransactionsTotalByTimePeriod(i->getName(), dates.first, dates.second);
    }
    return total;
}

std::multiset<SalaryIncome*> SystemDataSource::getSalaryIncomeTransactionsByTimePeriod(const QDate& startingPeriod, const QDate& endingPeriod) const
{
    return getTransactionsByTimePeriod(salaryIncomeList, startingPeriod, endingPeriod);
}

std::multiset<SupplementalIncome*> SystemDataSource::getSupplementalIncomeTransactionsByTimePeriod(const QDate& startingPeriod, const QDate& endingPeriod) const
{
    return getTransactionsByTimePeriod(supplementalIncomeList, startingPeriod, endingPeriod);
}

double SystemDataSource::getTotalIncomeTotalByTimePeriod(const QDate& startingPeriod, const QDate& endingPeriod) const
{
    return (getTransactionsTotalByTimePeriod(salaryIncomeList, startingPeriod, endingPeriod) +
           getTransactionsTotalByTimePeriod(supplementalIncomeList, startingPeriod, endingPeriod));
}

double SystemDataSource::getSalaryIncomeTotalByTimePeriod(const QDate& startingPeriod, const QDate& endingPeriod) const
{
    return getTransactionsTotalByTimePeriod(salaryIncomeList, startingPeriod, endingPeriod);
}

double SystemDataSource::getSupplementalIncomeTotalByTimePeriod(const QDate& startingPeriod, const QDate& endingPeriod) const
{
    return getTransactionsTotalByTimePeriod(supplementalIncomeList, startingPeriod, endingPeriod);
}

void SystemDataSource::addSalaryPayment(const SalaryIncome& payment)
{
    salaryIncomeList.insert(std::make_unique<SalaryIncome>(payment.getDate(),
                                                           payment.getAmount(),
                                                           payment.getOvertime()));

    QJsonArray array = obj.value("SalaryIncome").toArray();
    QJsonObject item;
    item.insert("Date", QJsonValue(payment.getDate().toString("MM/dd/yyyy")));
    item.insert("Amount", QJsonValue(payment.getAmount()));
    item.insert("Overtime", QJsonValue(static_cast<int>(payment.getOvertime())));
    array.append(item);
    obj["SalaryIncome"] = array;
}

void SystemDataSource::addSupplementalPayment(const SupplementalIncome& payment)
{
    supplementalIncomeList.insert(std::make_unique<SupplementalIncome>(payment.getDate(),
                                                                       payment.getAmount(),
                                                                       payment.getDescription()));

    QJsonArray array = obj.value("SupplementalIncome").toArray();
    QJsonObject item;
    item.insert("Date", QJsonValue(payment.getDate().toString("MM/dd/yyyy")));
    item.insert("Amount", QJsonValue(payment.getAmount()));
    item.insert("Description", QJsonValue(QString::fromStdString(payment.getDescription())));
    array.append(item);
    obj["SupplementalIncome"] = array;
}

double SystemDataSource::getMonthlyIncome() const
{
    std::pair<QDate, QDate> dates = DateUtilities::getCurrentMonthDates();
    return getTotalIncomeTotalByTimePeriod(dates.first, dates.second);
}

double SystemDataSource::getYearlyIncome() const
{
    std::pair<QDate, QDate> dates = DateUtilities::getCurrentYearDates();
    return getTotalIncomeTotalByTimePeriod(dates.first, dates.second);
}

std::vector<AssetEntry*> SystemDataSource::getAssetList() const
{
    std::vector<AssetEntry*> entries;
    entries.reserve(assetList.size());

    for(auto i = assetList.begin(); i != assetList.end(); ++i)
    {
        entries.push_back(i->get());
    }

    return entries;
}

std::vector<AssetEntry*> SystemDataSource::getAssetListByType(AssetType type) const
{
    std::vector<AssetEntry*> list;
    auto itr = assetList.begin();
    while((itr = std::find_if(itr, assetList.end(), [=] (const std::unique_ptr<AssetEntry>& entry){ return (entry->getType() == type); })) != assetList.end())
    {
        list.push_back(itr->get());
        itr++;
    }

    return list;
}

void SystemDataSource::addAsset(const AssetEntry& entry)
{
    assetList.push_back(std::make_unique<AssetEntry>(entry.getType(),
                                                     entry.getName(),
                                                     entry.getNetValue()));

    QJsonArray array = obj.value("Assets").toArray();
    QJsonObject item;
    item.insert("Type", QJsonValue(QString::fromStdString(AssetEntry::assetTypeToString(entry.getType()))));
    item.insert("Name", QJsonValue(QString::fromStdString(entry.getName())));
    item.insert("Value", QJsonArray());
    array.append(item);
    obj["Assets"] = array;
}

void SystemDataSource::addAssetValue(const std::string& assetName, const std::pair<QDate, double>& valueEntry)
{
    auto iterator = find_if(assetList.begin(), assetList.end(), [=] (std::unique_ptr<AssetEntry>& asset)
    {
        return (asset->getName() == assetName);
    });

    if(iterator != assetList.end())
    {
        iterator->get()->addValueEntry(valueEntry);

        QJsonArray array = obj.value("Assets").toArray();
        for(int i = 0; i < array.size(); ++i)
        {
            QJsonObject item = array.at(i).toObject();
            if(QString(item.value("Name").toString()).toStdString() == assetName)
            {

                QJsonArray values = item.value("Values").toArray();

                QJsonObject newValueItem;
                newValueItem.insert("Date", QJsonValue(valueEntry.first.toString("MM/dd/yyyy")));
                newValueItem.insert("Value", QJsonValue(valueEntry.second));
                values.append(newValueItem);
                item.remove("Values");
                item.insert("Values", values);
                array.removeAt(i);
                array.insert(i,item);
            }
        }
        obj["Assets"] = array;
    }
}



void SystemDataSource::parseExpenseTypes()
{
    QJsonValue expTypes = obj.value("ExpenseTypes");
    QJsonArray array = expTypes.toArray();
    for (const QJsonValue item : array)
    {
        const std::string& name = QString(item.toObject().value("Name").toString()).toStdString();
        const double budget = item.toObject().value("MonthlyBudget").toDouble();
        ExpenseType type(name, budget);
        expenseTypes.push_back(std::make_unique<ExpenseType>(name, budget));

        ExpenseType* expense = expenseTypes.back().get();
        QJsonArray transArray = item.toObject().value("Transactions").toArray();
        for(const QJsonValue trans : transArray)
        {
            QDate date;
            const double amount = trans.toObject().value("Amount").toDouble();
            const std::string& description = QString(trans.toObject().value("Description").toString()).toStdString();
            date = date.fromString(trans.toObject().value("Date").toString(), "MM/dd/yyyy");
            ExpenseTransaction transaction(date, amount, description);
            expense->addExpenseTransaction(transaction);
        }
    }

    qDebug() << "Expense Types: ";
    for(const auto& i:expenseTypes)
    {
        qDebug() << QString::fromStdString(i->getName()) << " " << i->getMonthlyBudget();
    }
}

void SystemDataSource::parseInvestmentTypes()
{
    QJsonValue invTypes = obj.value("InvestmentTypes");
    QJsonArray array = invTypes.toArray();
    for (const QJsonValue item : array)
    {
        const std::string& name = item.toObject().value("Name").toString().toStdString();
        const double target = item.toObject().value("MonthlyTarget").toDouble();
        investmentTypes.push_back(std::make_unique<InvestmentType>(name, target));

        InvestmentType* investment = investmentTypes.back().get();
        QJsonArray transArray = item.toObject().value("Transactions").toArray();
        for(const QJsonValue trans : transArray)
        {
            QDate date;
            const double amount = trans.toObject().value("Amount").toDouble();
            date = date.fromString(trans.toObject().value("Date").toString(), "MM/dd/yyyy");
            InvestmentTransaction transaction(date, amount);
            investment->addInvestmentTransaction(transaction);
        }
    }

    qDebug() << "Investment Types: ";
    for(const auto& i:investmentTypes)
    {
        qDebug() << QString::fromStdString(i->getName()) << " " << i->getMonthlyTarget();
    }
}

void SystemDataSource::parseAutomaticMonthlyPayments()
{
    QJsonValue autoPayments = obj.value("AutomaticMonthlyPayments");
    QJsonArray array = autoPayments.toArray();
    for (const QJsonValue item : array)
    {
        const std::string name = QString(item.toObject().value("Name").toString()).toStdString();
        const std::string account = QString(item.toObject().value("Account").toString()).toStdString();
        const double amount = item.toObject().value("Amount").toDouble();

        automaticMonthlyPaymentList.push_back(std::make_unique<AutomaticMonthlyPayment>(name, account, amount));
    }

    qDebug() << "Automatic Monthly Payments: ";
    for(const auto& i:automaticMonthlyPaymentList)
    {
        qDebug() << QString::fromStdString(i->getName()) << " " << i->getAmount();
    }
}

void SystemDataSource::parseSalaryIncome()
{
    QJsonValue salaryIncome = obj.value("SalaryIncome");
    QJsonArray array = salaryIncome.toArray();
    for (const QJsonValue item : array)
    {
        QDate date;
        date = date.fromString(item.toObject().value("Date").toString(), "MM/dd/yyyy");
        const double amount = item.toObject().value("Amount").toDouble();
        const unsigned overtime = static_cast<unsigned>(item.toObject().value("Overtime").toInt());

        salaryIncomeList.insert(std::make_unique<SalaryIncome>(date, amount, overtime));
    }

    qDebug() << "Salary Income: ";
    for(const auto& i:salaryIncomeList)
    {
        qDebug() << i->getDate().toString() << " " << i->getAmount();
    }
}

void SystemDataSource::parseSupplementalIncome()
{
    QJsonValue supplementalIncome = obj.value("SupplementalIncome");
    QJsonArray array = supplementalIncome.toArray();
    for (const QJsonValue item : array)
    {
        QDate date;
        date = date.fromString(item.toObject().value("Date").toString(), "MM/dd/yyyy");
        const double amount = item.toObject().value("Amount").toDouble();
        const std::string& description = QString(item.toObject().value("Description").toString()).toStdString();

        supplementalIncomeList.insert(std::make_unique<SupplementalIncome>(date, amount, description));
    }

    qDebug() << "Supplemental Income: ";
    for(const auto& i:supplementalIncomeList)
    {
        qDebug() << i->getDate() << " " << i->getAmount();
    }
}

void SystemDataSource::parseAssetList()
{
    QJsonValue assets = obj.value("Assets");
    QJsonArray array = assets.toArray();
    for (const QJsonValue item : array)
    {
        std::map<QDate, double> values;

        const std::string name = QString(item.toObject().value("Name").toString()).toStdString();
        const AssetType type = AssetEntry::stringToAssetType(QString(item.toObject().value("Type").toString().toLower()).toStdString());

        QJsonArray valueArray = item.toObject().value("Values").toArray();
        for (const QJsonValue valueItem : valueArray)
        {
            QDate tempDate;
            tempDate = tempDate.fromString(valueItem.toObject().value("Date").toString(), "MM/dd/yyyy");
            values.insert({tempDate, valueItem.toObject().value("Value").toDouble()});
        }

        assetList.push_back(std::make_unique<AssetEntry>(type, name, values));
    }

    qDebug() << "Assets: ";
    for(const auto& i:assetList)
    {
        qDebug() << QString::fromStdString(i->getName());
        for(auto j:i->getNetValue())
        {
            qDebug() << j.first << "  " << j.second;
        }
    }
}

template<typename Transaction>
std::multiset<Transaction*> SystemDataSource::getTransactionsByTimePeriod(const std::multiset<std::unique_ptr<Transaction>, TransactionComparison<Transaction>>& set,
                                                                          const QDate& startingPeriod,
                                                                          const QDate& endingPeriod) const
{
    std::multiset<Transaction*> matchingTransactions;

    auto lowerItr = set.lower_bound(std::make_unique<Transaction>(startingPeriod));
    auto upperItr = set.upper_bound(std::make_unique<Transaction>(endingPeriod));

    for(auto i = lowerItr; i != upperItr; ++i)
    {
        matchingTransactions.insert(i->get());
    }

    return matchingTransactions;
}

template<typename Transaction>
double SystemDataSource::getTransactionsTotalByTimePeriod(const std::multiset<std::unique_ptr<Transaction>, TransactionComparison<Transaction>>& set,
                                                          const QDate& startingPeriod,
                                                          const QDate& endingPeriod) const
{
    std::multiset<Transaction*> matchingTransactions;

    auto lowerItr = set.lower_bound(std::make_unique<Transaction>(startingPeriod));
    auto upperItr = set.upper_bound(std::make_unique<Transaction>(endingPeriod));

    double total = 0.0;
    for(auto i = lowerItr; i != upperItr; ++i)
    {
        total += i->get()->getAmount();
    }

    return total;
}

template<typename Type>
typename std::vector<std::unique_ptr<Type>>::const_iterator SystemDataSource::findMatchingType(const std::vector<std::unique_ptr<Type>>& list,
                                                                                               const std::string& name) const
{
    auto itr = std::find_if(list.begin(), list.end(), [=] (const std::unique_ptr<Type>& type)
    {
        return (type->getName() == name);
    });
    return  itr;
}
