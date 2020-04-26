#include "assetentry.h"
#include "automaticmonthlypayment.h"
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

SystemDataSource::SystemDataSource(const std::string filePath) : systemConfigFile(QString::fromStdString(filePath)) {}

SystemDataSource::~SystemDataSource() = default;

std::vector<ExpenseType*> SystemDataSource::getExpenseTypes() const
{
    return {};
}

std::multiset<ExpenseTransaction*> SystemDataSource::getExpenseTransactions() const
{
    return {};
}

std::multiset<ExpenseTransaction*> SystemDataSource::getExpenseTransactionsByTimePeriod(QDate startingPeriod, QDate endingPeriod) const
{
    return {};
}

std::vector<AutomaticMonthlyPayment*> SystemDataSource::getAutomaticMonthlyPayments() const
{
    return {};
}

void SystemDataSource::addExpenseType(const ExpenseType& type)
{
    expenseTypes.push_back(std::make_unique<ExpenseType>(type.getName(), type.getMonthlyBudget()));

    QJsonArray array = obj.value("ExpenseTypes").toArray();
    QJsonObject item;
    item.insert("MonthlyBudget", QJsonValue(type.getMonthlyBudget()));
    item.insert("Name", QJsonValue(QString::fromStdString(type.getName())));
    array.append(item);
    obj["ExpenseTypes"] = array;

}

void SystemDataSource::addExpenseTransaction(const ExpenseTransaction& transaction)
{
    expenseTransactionList.insert(std::make_unique<ExpenseTransaction>(transaction.getDate(),
                                                                       transaction.getAmount(),
                                                                       transaction.getType(),
                                                                       transaction.getDescription()));

    QJsonArray array = obj.value("Expenses").toArray();
    QJsonObject item;
    item.insert("Amount", QJsonValue(transaction.getAmount()));
    item.insert("Date", QJsonValue(transaction.getDate().toString("MM/dd/yyyy")));
    item.insert("Description", QJsonValue(QString::fromStdString(transaction.getDescription())));
    item.insert("Type", QJsonValue(QString::fromStdString(transaction.getType())));
    array.append(item);
    obj["Expenses"] = array;
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

std::vector<InvestmentType*> SystemDataSource::getInvestmentTypes() const
{
    return {};
}

std::multiset<InvestmentTransaction*> SystemDataSource::getInvestmentTransactions() const
{
    return {};
}

std::multiset<InvestmentTransaction*> SystemDataSource::getInvestmentTransactionsByTimePeriod(QDate startingPeriod, QDate endingPeriod) const
{
    return {};
}

void SystemDataSource::addInvestmentType(const InvestmentType& type)
{
    investmentTypes.push_back(std::make_unique<InvestmentType>(type.getName(), type.getMonthlyTarget()));

    QJsonArray array = obj.value("InvestmentTypes").toArray();
    QJsonObject item;
    item.insert("MonthlyTarget", QJsonValue(type.getMonthlyTarget()));
    item.insert("Name", QJsonValue(QString::fromStdString(type.getName())));
    array.append(item);
    obj["InvestmentTypes"] = array;
}

void SystemDataSource::addInvestmentTransaction(const InvestmentTransaction& transaction)
{
    investmentTransactionList.insert(std::make_unique<InvestmentTransaction>(transaction.getDate(),
                                                                             transaction.getAmount(),
                                                                             transaction.getType()));

    QJsonArray array = obj.value("Investments").toArray();
    QJsonObject item;
    item.insert("Amount", QJsonValue(transaction.getAmount()));
    item.insert("Date", QJsonValue(transaction.getDate().toString("MM/dd/yyyy")));
    item.insert("Type", QJsonValue(QString::fromStdString(transaction.getType())));
    array.append(item);
    obj["Investments"] = array;
}

std::multiset<SalaryIncome*> SystemDataSource::getSalaryIncomeTransactionsByTimePeriod(QDate startingPeriod, QDate endingPeriod) const
{
    return {};
}

std::multiset<SupplementalIncome*> SystemDataSource::getSupplementalIncomeTransactionsByTimePeriod(QDate startingPeriod, QDate endingPeriod) const
{
    return {};
}

double SystemDataSource::getTotalIncomeByTimePeriod(QDate startingPeriod, QDate endingPeriod) const
{
    return 0.0;
}

double SystemDataSource::getSalaryIncomeByTimePeriod(QDate startingPeriod, QDate endingPeriod) const
{
    return 0.0;
}

std::vector<AssetEntry*> SystemDataSource::getAssetList() const
{
    return {};
}

std::vector<AssetEntry*> SystemDataSource::getAssetListByType(AssetType type) const
{
    return {};
}

void SystemDataSource::createSystemConfigurationTemplate()
{
    systemConfigFile.setFileName("../CashFlowManager/SystemConfiguration.json");
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
    obj.insert("Expenses", empty);
    obj.insert("InvestmentTypes", empty);
    obj.insert("Investments", empty);
    obj.insert("MortgageInformation", empty);
    obj.insert("SalaryIncome", empty);
    obj.insert("SupplementalIncome", empty);
}

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
    parseExpenseTransactionList();
    parseInvestmentTypes();
    parseInvestmentTransactionList();
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

void SystemDataSource::parseExpenseTypes()
{
    QJsonValue expTypes = obj.value("ExpenseTypes");
    QJsonArray array = expTypes.toArray();
    for (const QJsonValue item : array)
    {
        const std::string& name = QString(item.toObject().value("Name").toString()).toStdString();
        const double budget = item.toObject().value("MonthlyBudget").toDouble();

        expenseTypes.push_back(std::make_unique<ExpenseType>(name, budget));
    }

    qDebug() << "Expense Types: ";
    for(const auto& i:expenseTypes)
    {
        qDebug() << QString::fromStdString(i->getName()) << " " << i->getMonthlyBudget();
    }
}

void SystemDataSource::parseExpenseTransactionList()
{
    QJsonValue expList = obj.value("Expenses");
    QJsonArray array = expList.toArray();
    for (const QJsonValue item : array)
    {
        QDate date;
        const std::string& type = QString(item.toObject().value("Type").toString()).toStdString();
        const std::string& description = QString(item.toObject().value("Description").toString()).toStdString();
        date = date.fromString(item.toObject().value("Date").toString(), "MM/dd/yyyy");
        const double amount = item.toObject().value("Amount").toDouble();

        expenseTransactionList.insert(std::make_unique<ExpenseTransaction>(date, amount, type, description));
    }

    qDebug() << "Expense Transaction List: ";
    for(const auto& i:expenseTransactionList)
    {
        qDebug() << QString::fromStdString(i->getType()) << " " << i->getDate();
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
    }

    qDebug() << "Investment Types: ";
    for(const auto& i:investmentTypes)
    {
        qDebug() << QString::fromStdString(i->getName()) << " " << i->getMonthlyTarget();
    }
}

void SystemDataSource::parseInvestmentTransactionList()
{
    QJsonValue invList = obj.value("Investments");
    QJsonArray array = invList.toArray();
    for (const QJsonValue item : array)
    {
        QDate date;
        const std::string type = QString(item.toObject().value("Type").toString()).toStdString();
        date = date.fromString(item.toObject().value("Date").toString(), "MM/dd/yyyy");
        const double amount = item.toObject().value("Amount").toDouble();

        investmentTransactionList.insert(std::make_unique<InvestmentTransaction>(date, amount, type));
    }

    qDebug() << "Investment Transaction List: ";
    for(const auto& i:investmentTransactionList)
    {
        qDebug() << QString::fromStdString(i->getType()) << " " << i->getDate();
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
        date = date = date.fromString(item.toObject().value("Date").toString(), "MM/dd/yyyy");
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
        const AssetType type = stringToAssetType(QString(item.toObject().value("Name").toString().toLower()).toStdString());

        QJsonArray valueArray = item.toObject().value("Value").toArray();
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

std::string SystemDataSource::assetTypeToString(AssetType type)
{
    if(type == AssetType::Liquid)
    {
        return "Liquid";
    }
    else if(type == AssetType::Illiquid)
    {
        return "Illiquid";
    }

    return "Unknown";
}

AssetType SystemDataSource::stringToAssetType(std::string type)
{
    if(type == "liquid")
    {
        return AssetType::Liquid;
    }
    else if(type == "illiquid")
    {
        return AssetType::Illiquid;
    }

    return AssetType::Unknown;
}
