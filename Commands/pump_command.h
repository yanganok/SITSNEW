#ifndef PUMP_COMMAND_H
#define PUMP_COMMAND_H

#include <QObject>
#include "command.h"
class Pump_Command : public Command
{
    Q_OBJECT
public:
    Pump_Command();
    Pump_Command(InstrumentOperator* operate, Response *response, int msec = -1, QString key = "", bool async = false, int delayMs = 0);
protected:
    static int _curPos;
};

#endif // PUMP_COMMAND_H
