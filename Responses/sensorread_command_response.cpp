#include "sensorread_command_response.h"

SensorRead_Command_Response::SensorRead_Command_Response()
{
    _typeName = classtype();
}

SensorRead_Command_Response::SensorRead_Command_Response(int cmdId, SensorType type, CommunicateCoreUnderlying::PressureSensorDeviceID deviceId, qint32 curPressure, QString key)
    :_type(type), Response(cmdId, key),  _deviceId(deviceId), _curPressure(curPressure)
{
    _typeName = classtype();
}
