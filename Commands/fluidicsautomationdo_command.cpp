#include "fluidicsautomationdo_command.h"

FluidicsAutomationDo_Command::FluidicsAutomationDo_Command()
{

}

FluidicsAutomationDo_Command::FluidicsAutomationDo_Command(InstrumentOperator *operate,  Response *response, int msec, FluidicsAutomationOperate op)
    :Command(operate, response, msec), _op(op)
{

}

bool FluidicsAutomationDo_Command::package(QByteArray &arr)
{
    return true;
}

bool FluidicsAutomationDo_Command::packageToResponse(QByteArray &arr)
{
    return true;
}
