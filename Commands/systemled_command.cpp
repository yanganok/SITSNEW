#include "systemled_command.h"

SystemLED_Command::SystemLED_Command()
{

}

SystemLED_Command::SystemLED_Command(InstrumentOperator *operate,  Response *response, int msec, quint8 r, quint8 g, quint8 b)
    :Command(operate, response, msec), _r(r), _g(g), _b(b)
{

}

bool SystemLED_Command::package(QByteArray &arr)
{
    return true;
}

bool SystemLED_Command::packageToResponse(QByteArray &arr)
{
    return true;
}
