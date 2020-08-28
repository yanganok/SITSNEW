#include "pumpdispense_command_response.h"

PumpDispense_Command_Response::PumpDispense_Command_Response()
{

}

PumpDispense_Command_Response::PumpDispense_Command_Response(int cmdId, CommunicateCoreUnderlying::SyringPumpId deviceId, quint32 curPos, QString key):Response(cmdId, key)
{
    _deviceId = deviceId;
    _curPos = curPos;
    _typeName = classtype();
}
