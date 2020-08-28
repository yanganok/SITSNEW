#include "xyemergencystop_commmand_response.h"

XYEmergencyStop_Commmand_Response::XYEmergencyStop_Commmand_Response()
{
    _typeName = classtype();
}

XYEmergencyStop_Commmand_Response::XYEmergencyStop_Commmand_Response(int cmdId, CommunicateCoreUnderlying::XYStageDeviceId deviceId,  CommunicateCoreUnderlying::XYStageStatusWord status)
    :Response(cmdId), _deviceId(deviceId)
{
    _typeName = classtype();
}
