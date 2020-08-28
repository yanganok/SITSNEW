#ifndef BUBBLEGETCOUNT_COMMAND_H
#define BUBBLEGETCOUNT_COMMAND_H

#include <QObject>
#include "command.h"

class BubbleGetCount_Command : public Command
{
    Q_OBJECT
public:
    BubbleGetCount_Command();
    BubbleGetCount_Command(InstrumentOperator* operate,  Response *response, int msec, quint8 sensor);
public:
    inline quint8 sensor()const{return _sensor;}
protected:
    bool package(QByteArray& arr) override;
    bool packageToResponse(QByteArray& arr) override;
private:
    quint8 _sensor;
signals:

};

#endif // BUBBLEGETCOUNT_COMMAND_H
