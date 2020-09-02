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
INCLUDEPATH += Utilities/

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
        Expense/addexpensetransactiondialog.cpp \
        Expense/addexpensetransactiondialogcontroller.cpp \
        Expense/addexpensetypedialog.cpp \
        Expense/addexpensetypedialogcontroller.cpp \
        Income/addincometransactiondialog.cpp \
        Income/addincometransactiondialogcontroller.cpp \
        Investment/addinvestmenttransactiondialog.cpp \
        Investment/addinvestmenttransactiondialogcontroller.cpp \
        Investment/addinvestmenttypedialog.cpp \
        Investment/addinvestmenttypedialogcontroller.cpp \
        Asset/assetsummarydialog.cpp \
        Asset/assetsummarydialogcontroller.cpp \
        Expense/automaticmonthlypaymentsummarydialog.cpp \
        Mortgage/updatemortgageinfodialogcontroller.cpp \
        Utilities/basetransaction.cpp \
        Utilities/currencyutilities.cpp \
        Utilities/dateutilities.cpp \
        Expense/expensetypesummarydialog.cpp \
        appexception.cpp \
        cashflowmanagerapplication.cpp \
        Expense/expensetypeselectdialog.cpp \
        main.cpp \
        mainwindow.cpp \
        mainwindowcontroller.cpp \
        monthlybudgetsummarydialog.cpp \
        Mortgage/mortgagesummarydialog.cpp \
        systemdatasource.cpp \
        Asset/updateassetinfodialog.cpp \
        Asset/updateassetinfodialogcontroller.cpp \
        Expense/updateautomaticmonthlypaymentsdialog.cpp \
        Expense/updateautomaticmonthlypaymentsdialogcontroller.cpp \
        Utilities/validator.cpp \
        Mortgage/updatemortgageinfodialog.cpp \
        yearlybudgetsummarydialog.cpp \
        Income/yearlyincomesummarydialog.cpp

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
        Expense/addexpensetransactiondialog.h \
        Expense/addexpensetransactiondialogcontroller.h \
        Expense/addexpensetypedialog.h \
        Expense/addexpensetypedialogcontroller.h \
        Income/addincometransactiondialog.h \
        Income/addincometransactiondialogcontroller.h \
        Investment/addinvestmenttransactiondialog.h \
        Investment/addinvestmenttransactiondialogcontroller.h \
        Investment/addinvestmenttypedialog.h \
        Investment/addinvestmenttypedialogcontroller.h \
        Asset/assetsummarydialog.h \
        Asset/assetsummarydialogcontroller.h \
        Expense/automaticmonthlypaymentsummarydialog.h \
        Mortgage/updatemortgageinfodialogcontroller.h \
        Utilities/basetransaction.h \
        Utilities/currencyutilities.h \
        Utilities/dateutilities.h \
        Expense/expensetypesummarydialog.h \
        appexception.h \
        cashflowmanagerapplication.h \
        errorcode.h \
        Expense/expensetypeselectdialog.h \
        mainwindow.h \
        mainwindowcontroller.h \
        monthlybudgetsummarydialog.h \
        Mortgage/mortgagesummarydialog.h \
        systemdatasource.h \
        Utilities/transactioncomparison.h \
        Asset/updateassetinfodialog.h \
        Asset/updateassetinfodialogcontroller.h \
        Expense/updateautomaticmonthlypaymentsdialog.h \
        Expense/updateautomaticmonthlypaymentsdialogcontroller.h \
        Utilities/validator.h \
        Mortgage/updatemortgageinfodialog.h \
        yearlybudgetsummarydialog.h \
        Income/yearlyincomesummarydialog.h

FORMS += \
        addexpensetransactiondialog.ui \
        addexpensetypedialog.ui \
        addincometransactiondialog.ui \
        addinvestmenttransactiondialog.ui \
        addinvestmenttypedialog.ui \
        assetsummarydialog.ui \
        automaticmonthlypaymentsummarydialog.ui \
        expensetypeselectdialog.ui \
        expensetypesummarydialog.ui \
        mainwindow.ui \
        monthlybudgetsummarydialog.ui \
        mortgagesummarydialog.ui \
        updateassetinfodialog.ui \
        updateautomaticmonthlypaymentsdialog.ui \
        updatemortgageinfodialog.ui \
        yearlybudgetsummarydialog.ui \
        yearlyincomesummarydialog.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
