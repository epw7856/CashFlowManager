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

RC_ICONS = app_icon.ico

SOURCES += \
        Asset/assetentry.cpp \
        Asset/assetlisttablemodel.cpp \
        Expense/automaticmonthlypayment.cpp \
        Expense/automaticmonthlypaymenttablemodel.cpp \
        Expense/expensetransaction.cpp \
        Expense/expensetype.cpp \
        Expense/expensetypetablemodel.cpp \
        Expense/monthlyexpensetablemodel.cpp \
        Expense/yearlyexpensetablemodel.cpp \
        Income/salaryincome.cpp \
        Income/salaryincometablemodel.cpp \
        Income/supplementalincome.cpp \
        Income/supplementalincometablemodel.cpp \
        Investment/investmenttransaction.cpp \
        Investment/investmenttype.cpp \
        Investment/monthlyinvestmenttablemodel.cpp \
        Investment/yearlyinvestmenttablemodel.cpp \
        Mortgage/mortgageinformation.cpp \
        Mortgage/mortgageprincipalpayment.cpp \
        Mortgage/mortgagetablemodel.cpp \
        addexpensetransactiondialog.cpp \
        addexpensetransactiondialogcontroller.cpp \
        addexpensetypedialog.cpp \
        addexpensetypedialogcontroller.cpp \
        addinvestmenttransactiondialog.cpp \
        assetsummarydialog.cpp \
        assetsummarydialogcontroller.cpp \
        automaticmonthlypaymentsummarydialog.cpp \
        basetransaction.cpp \
        currencyutilities.cpp \
        dateutilities.cpp \
        expensetypesummarydialog.cpp \
        main.cpp \
        mainwindow.cpp \
        mainwindowcontroller.cpp \
        monthlybudgetsummarydialog.cpp \
        mortgagesummarydialog.cpp \
        systemdatasource.cpp \
        validator.cpp \
        yearlybudgetsummarydialog.cpp \
        yearlyincomesummarydialog.cpp

HEADERS += \
        Asset/assetentry.h \
        Asset/assetinterface.h \
        Asset/assetlisttablemodel.h \
        Asset/assettype.h \
        Expense/automaticmonthlypayment.h \
        Expense/automaticmonthlypaymenttablemodel.h \
        Expense/expenseinterface.h \
        Expense/expensetransaction.h \
        Expense/expensetype.h \
        Expense/expensetypetablemodel.h \
        Expense/monthlyexpensetablemodel.h \
        Expense/yearlyexpensetablemodel.h \
        Income/incomeinterface.h \
        Income/salaryincome.h \
        Income/salaryincometablemodel.h \
        Income/supplementalincome.h \
        Income/supplementalincometablemodel.h \
        Investment/investmentinterface.h \
        Investment/investmenttransaction.h \
        Investment/investmenttype.h \
        Investment/monthlyinvestmenttablemodel.h \
        Investment/yearlyinvestmenttablemodel.h \
        Mortgage/mortgageinformation.h \
        Mortgage/mortgageinterface.h \
        Mortgage/mortgageprincipalpayment.h \
        Mortgage/mortgagetablemodel.h \
        addexpensetransactiondialog.h \
        addexpensetransactiondialogcontroller.h \
        addexpensetypedialog.h \
        addexpensetypedialogcontroller.h \
        addinvestmenttransactiondialog.h \
        assetsummarydialog.h \
        assetsummarydialogcontroller.h \
        automaticmonthlypaymentsummarydialog.h \
        basetransaction.h \
        currencyutilities.h \
        dateutilities.h \
        expensetypesummarydialog.h \
        mainwindow.h \
        mainwindowcontroller.h \
        monthlybudgetsummarydialog.h \
        mortgagesummarydialog.h \
        systemdatasource.h \
        transactioncomparison.h \
        validator.h \
        yearlybudgetsummarydialog.h \
        yearlyincomesummarydialog.h

FORMS += \
        addexpensetransactiondialog.ui \
        addexpensetypedialog.ui \
        addinvestmenttransactiondialog.ui \
        assetsummarydialog.ui \
        automaticmonthlypaymentsummarydialog.ui \
        expensetypesummarydialog.ui \
        mainwindow.ui \
        monthlybudgetsummarydialog.ui \
        mortgagesummarydialog.ui \
        yearlybudgetsummarydialog.ui \
        yearlyincomesummarydialog.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
