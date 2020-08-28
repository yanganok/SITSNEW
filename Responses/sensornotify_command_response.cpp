#include "sensornotify_command_response.h"

SensorNotify_Command_Response::SensorNotify_Command_Response()
{
    _typeName = classtype();
}

SensorNotify_Command_Response::SensorNotify_Command_Response(SensorType type, bool state)
    :_type(type), _state(state)
{
    _typeName = classtype();
}
