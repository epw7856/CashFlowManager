#include <QByteArray>
#include <QFile>
#include <QJsonArray>
#include <QJsonDocument>
#include "systemdatasource.h"
#include <QDebug>

std::vector<ExpenseType> SystemDataSource::getExpenseTypes() const
{
    return expenseTypes;
}

std::multiset<ExpenseTransaction> SystemDataSource::getExpenseTransactions() const
{
    return expenseTransactionList;
}

std::multiset<ExpenseTransaction> SystemDataSource::getExpenseTransactionsByTimePeriod(QDate startingPeriod, QDate endingPeriod) const
{
    return {};
}

std::vector<AutomaticMonthlyPayment> SystemDataSource::getAutomaticMonthlyPayments() const
{
    return automaticMonthlyPaymentList;
}

std::vector<InvestmentType> SystemDataSource::getInvestmentTypes() const
{
    return investmentTypes;
}

std::multiset<InvestmentTransaction> SystemDataSource::getInvestmentTransactions() const
{
    return investmentTransactionList;
}

std::multiset<InvestmentTransaction> SystemDataSource::getInvestmentTransactionsByTimePeriod(QDate startingPeriod, QDate endingPeriod) const
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

}

void SystemDataSource::parseExpenseTypes(const QJsonObject& obj)
{
    QJsonValue expTypes = obj.value("ExpenseTypes");
    QJsonArray array = expTypes.toArray();
    for (const QJsonValue item : array)
    {
        ExpenseType type;

        type.Name = QString(item.toObject().value("Name").toString()).toStdString();
        type.MonthlyBudget = item.toObject().value("MonthlyBudget").toDouble();

        expenseTypes.push_back(type);
    }

    qDebug() << "Expense Types: ";
    for(auto i:expenseTypes)
    {
        qDebug() << QString::fromStdString(i.Name) << " " << i.MonthlyBudget;
    }
}

void SystemDataSource::parseExpenseTransactionList(const QJsonObject &obj)
{
    QJsonValue expList = obj.value("Expenses");
    QJsonArray array = expList.toArray();
    for (const QJsonValue item : array)
    {
        QDate tempDate;
        ExpenseTransaction entry;

        entry.Type = QString(item.toObject().value("Type").toString()).toStdString();
        entry.Description = QString(item.toObject().value("Description").toString()).toStdString();
        entry.Date = tempDate.fromString(item.toObject().value("Date").toString(), "MM/dd/yyyy");
        entry.Amount = item.toObject().value("Amount").toDouble();

        expenseTransactionList.insert(entry);
    }

    qDebug() << "Expense Transaction List: ";
    for(auto i:expenseTransactionList)
    {
        qDebug() << QString::fromStdString(i.Type) << " " << i.Date;
    }
}

void SystemDataSource::parseInvestmentTypes(const QJsonObject &obj)
{
    QJsonValue expTypes = obj.value("InvestmentTypes");
    QJsonArray array = expTypes.toArray();
    for (const QJsonValue item : array)
    {
        InvestmentType type;

        type.Name = QString(item.toObject().value("Name").toString()).toStdString();
        type.MonthlyTarget = item.toObject().value("MonthlyTarget").toDouble();

        investmentTypes.push_back(type);
    }

    qDebug() << "Investment Types: ";
    for(auto i:investmentTypes)
    {
        qDebug() << QString::fromStdString(i.Name) << " " << i.MonthlyTarget;
    }
}

void SystemDataSource::parseInvestmentTransactionList(const QJsonObject &obj)
{
    QJsonValue expList = obj.value("Investments");
    QJsonArray array = expList.toArray();
    for (const QJsonValue item : array)
    {
        QDate tempDate;
        InvestmentTransaction entry;

        entry.Type = QString(item.toObject().value("Type").toString()).toStdString();
        entry.Date = tempDate.fromString(item.toObject().value("Date").toString(), "MM/dd/yyyy");
        entry.Amount = item.toObject().value("Amount").toDouble();

        investmentTransactionList.insert(entry);
    }

    qDebug() << "Investment Transaction List: ";
    for(auto i:investmentTransactionList)
    {
        qDebug() << QString::fromStdString(i.Type) << " " << i.Date;
    }
}

void SystemDataSource::parseAutomaticMonthlyPayments(const QJsonObject &obj)
{
    QJsonValue expTypes = obj.value("AutomaticMonthlyPayments");
    QJsonArray array = expTypes.toArray();
    for (const QJsonValue item : array)
    {
        AutomaticMonthlyPayment entry;

        entry.Name = QString(item.toObject().value("Name").toString()).toStdString();
        entry.Account = QString(item.toObject().value("Account").toString()).toStdString();
        entry.Amount = item.toObject().value("Amount").toDouble();

        automaticMonthlyPaymentList.push_back(entry);
    }

    qDebug() << "Automatic Monthly Payments: ";
    for(auto i:automaticMonthlyPaymentList)
    {
        qDebug() << QString::fromStdString(i.Name) << " " << i.Amount;
    }
}
