#include "sensoroverride_command.h"

SensorOverride_Command::SensorOverride_Command()
{

}

SensorOverride_Command::SensorOverride_Command(InstrumentOperator *operate,  Response *response, int msec, SensorType type, bool clear, bool state)
    :Command(operate, response, msec), _type(type), _clear(clear), _state(state)
{

}

bool SensorOverride_Command::package(QByteArray &arr)
{
    return true;
}

bool SensorOverride_Command::packageToResponse(QByteArray &arr)
{
    return true;
}
