#include "xyfindzero_command_response.h"

XYFindZero_Command_Response::XYFindZero_Command_Response()
{

}

XYFindZero_Command_Response::XYFindZero_Command_Response(int cmdId, CommunicateCoreUnderlying::XYStageDeviceId deviceId, CommunicateCoreUnderlying::XYStageStatusWord status, bool isXFindZero, bool isYFindZero)
    :Response(cmdId), _deviceId(deviceId), _isXFindZero(isXFindZero), _isYFindZero(isYFindZero)
{
    _typeName = classtype();
}
