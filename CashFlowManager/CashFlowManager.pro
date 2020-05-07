#-------------------------------------------------
#
# Project created by QtCreator 2020-04-20T08:01:04
#
#-------------------------------------------------

QT += core gui
QT += charts

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = CashFlowManager
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++14

INCLUDEPATH += Asset/
INCLUDEPATH += Expense/
INCLUDEPATH += Income/
INCLUDEPATH += Investment/
INCLUDEPATH += Mortgage/

SOURCES += \
        Asset/assetentry.cpp \
        Expense/automaticmonthlypayment.cpp \
        Expense/expensetablemodel.cpp \
        Expense/expensetransaction.cpp \
        Expense/expensetype.cpp \
        Income/salaryincome.cpp \
        Income/supplementalincome.cpp \
        Investment/investmenttransaction.cpp \
        Investment/investmenttype.cpp \
        Mortgage/mortgageinformation.cpp \
        basetransaction.cpp \
        budgetbreakdowncontroller.cpp \
        currencyutilities.cpp \
        dateutilities.cpp \
        main.cpp \
        mainwindow.cpp \
        systemdatasource.cpp

HEADERS += \
        Asset/assetentry.h \
        Asset/assetinterface.h \
        Asset/assettype.h \
        Expense/automaticmonthlypayment.h \
        Expense/expenseinterface.h \
        Expense/expensetablemodel.h \
        Expense/expensetransaction.h \
        Expense/expensetype.h \
        Income/incomeinterface.h \
        Income/salaryincome.h \
        Income/supplementalincome.h \
        Investment/investmentinterface.h \
        Investment/investmenttransaction.h \
        Investment/investmenttype.h \
        Mortgage/mortgageinformation.h \
        Mortgage/mortgagepayment.h \
        basetransaction.h \
        budgetbreakdowncontroller.h \
        currencyutilities.h \
        dateutilities.h \
        mainwindow.h \
        systemdatasource.h \
        transactioncomparison.h

FORMS += \
        mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
