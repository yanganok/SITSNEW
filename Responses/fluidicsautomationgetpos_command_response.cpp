#include "fluidicsautomationgetpos_command_response.h"

FluidicsAutomationGetPos_Command_Response::FluidicsAutomationGetPos_Command_Response()
{
    _typeName = classtype();
}

FluidicsAutomationGetPos_Command_Response::FluidicsAutomationGetPos_Command_Response(FluidicsAutomationPosition pos, QString raw)
    :_pos(pos), _raw(raw)
{
    _typeName = classtype();
}
