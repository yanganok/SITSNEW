#include "xyselfinspection_command_response.h"

XYSelfInspection_Command_Response::XYSelfInspection_Command_Response()
{
    _typeName = classtype();
}

XYSelfInspection_Command_Response::XYSelfInspection_Command_Response(int cmdId, CommunicateCoreUnderlying::XYStageDeviceId deviceId, CommunicateCoreUnderlying::XYStageStatusWord status)
    :Response(cmdId), _deviceId(deviceId), _status(status)
{
    _typeName = classtype();
}
