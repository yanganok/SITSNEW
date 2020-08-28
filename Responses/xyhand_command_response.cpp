#include "xyhand_command_response.h"

XYHand_Command_Response::XYHand_Command_Response()
{
    _typeName = classtype();
}

XYHand_Command_Response::XYHand_Command_Response(int cmdId, CommunicateCoreUnderlying::XYStageDeviceId deviceId, CommunicateCoreUnderlying::XYStageStatusWord status)
    :Response(cmdId), _deviceId(deviceId), _status(status)
{
    _typeName = classtype();
}

