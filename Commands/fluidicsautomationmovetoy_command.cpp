#include "fluidicsautomationmovetoy_command.h"

FluidicsAutomationMoveToY_Command::FluidicsAutomationMoveToY_Command()
{

}

FluidicsAutomationMoveToY_Command::FluidicsAutomationMoveToY_Command(InstrumentOperator *operate,  Response *response, int msec, FluidicsAutomationPosition pos)
    :Command(operate, response, msec), _pos(pos)
{

}

bool FluidicsAutomationMoveToY_Command::package(QByteArray &arr)
{
    return true;
}

bool FluidicsAutomationMoveToY_Command::packageToResponse(QByteArray &arr)
{
    return true;
}
