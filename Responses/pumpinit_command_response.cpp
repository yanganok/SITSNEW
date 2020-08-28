#include "pumpinit_command_response.h"

PumpInit_Command_Response::PumpInit_Command_Response()
{

}

PumpInit_Command_Response::PumpInit_Command_Response(int cmdId, CommunicateCoreUnderlying::SyringPumpId deviceId, CommunicateCoreUnderlying::SyringPumpStatusWord statusCode, int curStep, QString key)
    :_deviceId(deviceId), _statusCode(statusCode), Response(cmdId, key), _curPos(curStep)
{
    _typeName = classtype();
}
