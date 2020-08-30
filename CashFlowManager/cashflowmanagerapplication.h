#ifndef CASHFLOWMANAGERAPPLICATION_H
#define CASHFLOWMANAGERAPPLICATION_H

#include <QApplication>

class CashFlowManagerApplication : public QApplication
{
public:
  CashFlowManagerApplication(int& argc, char** argv);
  virtual ~CashFlowManagerApplication() {}

  // Reimplemented from QApplication in order for exceptions to be thrown from
  // event handlers (aka slots)
  virtual bool notify(QObject* receiver, QEvent* event);
};

#endif // CASHFLOWMANAGERAPPLICATION_H
