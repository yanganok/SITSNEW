#include "valvegetposition_command_response.h"

ValveGetPosition_Command_Response::ValveGetPosition_Command_Response()
{
    _typeName = classtype();
}

ValveGetPosition_Command_Response::ValveGetPosition_Command_Response(int cmdId, CommunicateCoreUnderlying::ValveDeviceId deviceId, int curPos, QString key)
    :Response(cmdId, key), _deviceId(deviceId), _curPos(curPos)
{
    _typeName = classtype();
}
