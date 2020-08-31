#include "valvemoveposition_command_response.h"

ValveMovePosition_Command_Response::ValveMovePosition_Command_Response()
{
    _typeName = classtype();
}

ValveMovePosition_Command_Response::ValveMovePosition_Command_Response(int cmdId, CommunicateCoreUnderlying::ValveDeviceId deviceId, int curPos, QString key)
    :Response(cmdId, key), _deviceId(deviceId), _curPos(curPos)
{
    _typeName = classtype();
}
