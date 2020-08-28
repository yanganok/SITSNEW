#ifndef TIMESETCLOCK_COMMAND_H
#define TIMESETCLOCK_COMMAND_H
#include "command.h"

class TimeSetClock_Command : public Command
{
    Q_OBJECT
public:
    TimeSetClock_Command();
    TimeSetClock_Command(InstrumentOperator* operate,  Response *response, int msec, quint32 seconds);
public:
    inline quint32 seconds()const{return _seconds;}
protected:
    bool package(QByteArray& arr) override;
    bool packageToResponse(QByteArray& arr) override;
private:
    quint32 _seconds;
};

#endif // TIMESETCLOCK_COMMAND_H
