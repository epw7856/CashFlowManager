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

std::set<ExpenseTransaction> SystemDataSource::getExpenseTransactions() const
{
    return expenseTransactionList;
}

std::set<ExpenseTransaction> SystemDataSource::getExpenseTransactionsByTimePeriod(QDate startingPeriod, QDate endingPeriod) const
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
    parseExpenseList(obj);


}

void SystemDataSource::parseExpenseTypes(const QJsonObject& obj)
{
    QJsonValue expTypes = obj.value("ExpenseTypes");
    QJsonArray array = expTypes.toArray();
    for (const QJsonValue item : array)
    {
        ExpenseType type;

        type.name = QString(item.toObject().value("Name").toString()).toStdString();
        type.monthlyBudget = item.toObject().value("MonthlyBudget").toDouble();

        expenseTypes.push_back(type);
    }

    qDebug() << "Expense Types: ";
    for(auto i:expenseTypes)
    {
        qDebug() << QString::fromStdString(i.name) << " " << i.monthlyBudget;
    }
}

void SystemDataSource::parseExpenseList(const QJsonObject &obj)
{
    QJsonValue expList = obj.value("Expenses");
    QJsonArray array = expList.toArray();
    for (const QJsonValue item : array)
    {
        QDate tempDate;
        ExpenseTransaction entry;

        entry.type = QString(item.toObject().value("Type").toString()).toStdString();
        entry.description = QString(item.toObject().value("Description").toString()).toStdString();
        entry.date = tempDate.fromString(item.toObject().value("Date").toString(), "MM/dd/yyyy");
        entry.amount = item.toObject().value("Amount").toDouble();

        expenseTransactionList.insert(entry);
    }

    qDebug() << "Expense Transaction List: ";
    for(auto i:expenseTransactionList)
    {
        qDebug() << QString::fromStdString(i.type) << " " << i.date;
    }
}
