#include "xymovetohomepoint_command_response.h"

XYMoveToHomePoint_Command_Response::XYMoveToHomePoint_Command_Response()
{
    _typeName = classtype();
}

XYMoveToHomePoint_Command_Response::XYMoveToHomePoint_Command_Response(int cmdId, CommunicateCoreUnderlying::XYStageDeviceId deviceId, CommunicateCoreUnderlying::XYStageStatusWord status)
    :Response(cmdId), _deviceId(deviceId), _status(status)
{
    _typeName = classtype();
}

