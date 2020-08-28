#include "humidityread_command.h"

HumidityRead_Command::HumidityRead_Command()
{

}

HumidityRead_Command::HumidityRead_Command(InstrumentOperator *operate,  Response *response, int msec, int millic)
    :Command(operate, response, msec), _millic(millic)
{

}

bool HumidityRead_Command::package(QByteArray &arr)
{
    return true;
}

bool HumidityRead_Command::packageToResponse(QByteArray &arr)
{
    return true;
}
