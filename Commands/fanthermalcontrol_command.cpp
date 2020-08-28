#include "fanthermalcontrol_command.h"

FanThermalControl_Command::FanThermalControl_Command()
{

}

FanThermalControl_Command::FanThermalControl_Command(InstrumentOperator *operate,  Response *response, int msec, bool enable)
    :Command(operate, response, msec),_enable(enable)
{

}

bool FanThermalControl_Command::package(QByteArray &arr)
{
    return true;
}

bool FanThermalControl_Command::packageToResponse(QByteArray &arr)
{
    return true;
}
