#include "timesetclock_command.h"

TimeSetClock_Command::TimeSetClock_Command()
{

}

TimeSetClock_Command::TimeSetClock_Command(InstrumentOperator *operate,  Response *response, int msec, quint32 seconds)
    :Command(operate, response, msec), _seconds(seconds)
{

}

bool TimeSetClock_Command::package(QByteArray &arr)
{
    return true;
}

bool TimeSetClock_Command::packageToResponse(QByteArray &arr)
{
    return true;
}
