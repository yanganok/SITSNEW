#include "fluidicsautomationreagenttrayctrl_command.h"

FluidicsAutomationReagentTrayCtrl_Command::FluidicsAutomationReagentTrayCtrl_Command()
{

}

FluidicsAutomationReagentTrayCtrl_Command::FluidicsAutomationReagentTrayCtrl_Command(InstrumentOperator *operate,  Response *response, int msec, FluidicsAutomationPosition pos)
    :Command(operate, response, msec), _pos(pos)
{

}

bool FluidicsAutomationReagentTrayCtrl_Command::package(QByteArray &arr)
{
    return true;
}

bool FluidicsAutomationReagentTrayCtrl_Command::packageToResponse(QByteArray &arr)
{
    return true;
}
