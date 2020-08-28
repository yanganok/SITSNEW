#include "pressuresensorread_command.h"

PressureSensorRead_Command::PressureSensorRead_Command()
{

}

PressureSensorRead_Command::PressureSensorRead_Command(InstrumentOperator* operate,  Response *response,
                                                       int msec, int sensor, quint8 readMsec)
    :Command(operate, response, msec), _sensor(sensor), _readMsec(readMsec)
{

}

bool PressureSensorRead_Command::package(QByteArray &arr)
{
    return true;
}

bool PressureSensorRead_Command::packageToResponse(QByteArray &arr)
{
    return true;
}
