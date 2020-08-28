#ifndef STATUS_INSTRUMENTOPERATOR_H
#define STATUS_INSTRUMENTOPERATOR_H

#include <QObject>
#include <QQmlEngine>
#include "instrumentoperator.h"

class Status_InstrumentOperator : public InstrumentOperator
{
    Q_OBJECT
    QML_ELEMENT
public:
    Status_InstrumentOperator(QObject *parent = nullptr);
public:
    Q_INVOKABLE void createInstance();

public slots:
    void getResponse(std::shared_ptr<Response> response) override;
};

#endif // STATUS_INSTRUMENTOPERATOR_H
