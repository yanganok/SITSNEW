#include "sensorposition_command.h"

SensorPosition_Command::SensorPosition_Command()
{

}

SensorPosition_Command::SensorPosition_Command(InstrumentOperator *operate,  Response *response, int msec)
    :Command(operate, response, msec)
{

}

bool SensorPosition_Command::package(QByteArray &arr)
{
    return true;
}

bool SensorPosition_Command::packageToResponse(QByteArray &arr)
{
    return true;
}
