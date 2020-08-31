#include "valveinit_command_response.h"

ValveInit_Command_Response::ValveInit_Command_Response()
{
    _typeName = classtype();
}

ValveInit_Command_Response::ValveInit_Command_Response(int cmdId, CommunicateCoreUnderlying::ValveDeviceId deviceId, CommunicateCoreUnderlying::ValveStatusWord statusCode, QString key)
    :Response(cmdId, key), _deviceId(deviceId), _statusCode(statusCode)
{
    _typeName = classtype();
}
