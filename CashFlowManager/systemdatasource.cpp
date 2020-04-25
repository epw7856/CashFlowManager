#include "assetentry.h"
#include "automaticmonthlypayment.h"
#include "expensetransaction.h"
#include "expensetype.h"
#include "investmenttransaction.h"
#include "investmenttype.h"
#include "mortgageinformation.h"
#include <QByteArray>
#include <QFile>
#include <QJsonArray>
#include <QJsonDocument>
#include <QDebug>
#include <QDate>
#include "salaryincome.h"
#include "supplementalincome.h"
#include "systemdatasource.h"

SystemDataSource::SystemDataSource() {}

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

void SystemDataSource::loadSystemConfig(std::string filePath)
{
    QFile file(QString::fromStdString(filePath));
    if(!file.open((QIODevice::ReadOnly | QIODevice::Text)))
    {
        qInfo() << "Unable to load System Configuration";
        return;
    }

    QByteArray rawData = file.readAll();
    file.close();
    QJsonDocument doc = QJsonDocument::fromJson(rawData);
    QJsonObject obj = doc.object();

    parseExpenseTypes(obj);
    parseExpenseTransactionList(obj);
    parseInvestmentTypes(obj);
    parseInvestmentTransactionList(obj);
    parseAutomaticMonthlyPayments(obj);
    parseSalaryIncome(obj);
    parseSupplementalIncome(obj);
    parseAssetList(obj);

}

void SystemDataSource::parseExpenseTypes(const QJsonObject& obj)
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

void SystemDataSource::parseExpenseTransactionList(const QJsonObject &obj)
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

void SystemDataSource::parseInvestmentTypes(const QJsonObject &obj)
{
    QJsonValue expTypes = obj.value("InvestmentTypes");
    QJsonArray array = expTypes.toArray();
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

void SystemDataSource::parseInvestmentTransactionList(const QJsonObject &obj)
{
    QJsonValue expList = obj.value("Investments");
    QJsonArray array = expList.toArray();
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

void SystemDataSource::parseAutomaticMonthlyPayments(const QJsonObject &obj)
{
    QJsonValue expTypes = obj.value("AutomaticMonthlyPayments");
    QJsonArray array = expTypes.toArray();
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

void SystemDataSource::parseSalaryIncome(const QJsonObject &obj)
{
    QJsonValue expTypes = obj.value("SalaryIncome");
    QJsonArray array = expTypes.toArray();
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

void SystemDataSource::parseSupplementalIncome(const QJsonObject &obj)
{
    QJsonValue expTypes = obj.value("SupplementalIncome");
    QJsonArray array = expTypes.toArray();
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
        qDebug() << i->getDate().toString() << " " << i->getAmount();
    }
}

void SystemDataSource::parseAssetList(const QJsonObject &obj)
{
    QJsonValue expTypes = obj.value("Assets");
    QJsonArray array = expTypes.toArray();
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
            qDebug() << j.first.toString() << "  " << j.second;
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
