#include "fanonoff_command.h"

FanOnOff_Command::FanOnOff_Command()
{

}

FanOnOff_Command::FanOnOff_Command(InstrumentOperator *operate,  Response *response, int msec, FanType fanType, bool on)
    :Command(operate, response, msec), _fanType(fanType), _on(on)
{

}

bool FanOnOff_Command::package(QByteArray &arr)
{
    return true;
}

bool FanOnOff_Command::packageToResponse(QByteArray &arr)
{
    return true;
}
