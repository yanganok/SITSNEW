#include "xygetposition_command_response.h"

XYGetPosition_Command_Response::XYGetPosition_Command_Response()
{
    _typeName = classtype();
}

XYGetPosition_Command_Response::XYGetPosition_Command_Response(int cmdId, CommunicateCoreUnderlying::XYStageDeviceId deviceId, int xPos, int yPos, CommunicateCoreUnderlying::XYStageStatusWord status)
    :Response(cmdId), _deviceId(deviceId), _status(status), _xPos(xPos), _yPos(yPos)
{
    _typeName = classtype();
}
