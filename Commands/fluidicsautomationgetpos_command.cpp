#include "fluidicsautomationgetpos_command.h"

FluidicsAutomationGetPos_Command::FluidicsAutomationGetPos_Command()
{

}

FluidicsAutomationGetPos_Command::FluidicsAutomationGetPos_Command(InstrumentOperator *operate,  Response *response, int msec)
    :Command(operate, response, msec)
{

}

bool FluidicsAutomationGetPos_Command::package(QByteArray &arr)
{
    return true;
}

bool FluidicsAutomationGetPos_Command::packageToResponse(QByteArray &arr)
{
    return true;
}
