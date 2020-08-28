#include "pumpabsorb_command_response.h"

PumpAbsorb_Command_Response::PumpAbsorb_Command_Response()
{
    _typeName = classtype();
}

PumpAbsorb_Command_Response::PumpAbsorb_Command_Response(int cmdId, CommunicateCoreUnderlying::SyringPumpId deviceId, quint32 curPos, QString key):Response(cmdId, key)
{
    _deviceId = deviceId;
    _curPos = curPos;
    _typeName = classtype();
}
