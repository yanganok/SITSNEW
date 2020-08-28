#include "xyinit_command_response.h"

XYInit_Command_Response::XYInit_Command_Response()
{
    _typeName = classtype();
}

XYInit_Command_Response::XYInit_Command_Response(int cmdId, CommunicateCoreUnderlying::XYStageDeviceId deviceId, CommunicateCoreUnderlying::XYStageStatusWord status)
    :Response(cmdId), _deviceId(deviceId), _status(status)
{
    _typeName = classtype();
}
