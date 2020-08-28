#include "xymovetosequencepoint_command_response.h"

XYMoveToSequencePoint_Command_Response::XYMoveToSequencePoint_Command_Response()
{
    _typeName = classtype();
}

XYMoveToSequencePoint_Command_Response::XYMoveToSequencePoint_Command_Response(int cmdId, CommunicateCoreUnderlying::XYStageDeviceId deviceId, CommunicateCoreUnderlying::XYStageStatusWord status)
    :Response(cmdId), _deviceId(deviceId), _status(status)
{
    _typeName = classtype();
}
