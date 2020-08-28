#include "flowcelldoorgetstate_command_response.h"

FlowcellDoorGetState_Command_Response::FlowcellDoorGetState_Command_Response()
{
    _typeName = classtype();
}

FlowcellDoorGetState_Command_Response::FlowcellDoorGetState_Command_Response(FlowcellDoorState state)
{
    _typeName = classtype();
}
