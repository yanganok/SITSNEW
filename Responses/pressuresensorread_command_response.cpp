#include "pressuresensorread_command_response.h"

PressureSensorRead_Command_Response::PressureSensorRead_Command_Response()
{
    _typeName = classtype();
}

PressureSensorRead_Command_Response::PressureSensorRead_Command_Response(int volts)
    :_volts(volts)
{
    _typeName = classtype();
}
