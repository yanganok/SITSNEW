#include "xymoveto_command_response.h"

XYMoveTo_Command_Response::XYMoveTo_Command_Response()
{
    _typeName = classtype();
}

XYMoveTo_Command_Response::XYMoveTo_Command_Response(int cmdId, CommunicateCoreUnderlying::XYStageDeviceId deviceId, int xPos, int yPos, CommunicateCoreUnderlying::XYStageStatusWord status)
    :Response(cmdId), _deviceId(deviceId), _status(status), _xPos(xPos), _yPos(yPos)
{
    _typeName = classtype();
}
