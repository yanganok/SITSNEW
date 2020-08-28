#include "fluidicsautomationbufferpresentcontrol_command.h"

FluidicsAutomationBufferPresentControl_Command::FluidicsAutomationBufferPresentControl_Command()
{

}

FluidicsAutomationBufferPresentControl_Command::FluidicsAutomationBufferPresentControl_Command(InstrumentOperator *operate,  Response *response, int msec, bool disable)
   :Command(operate, response, msec),  _disable(disable)
{

}

bool FluidicsAutomationBufferPresentControl_Command::package(QByteArray &arr)
{
    return true;
}

bool FluidicsAutomationBufferPresentControl_Command::packageToResponse(QByteArray &arr)
{
    return true;
}
