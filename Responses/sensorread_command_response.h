#ifndef SENSORREAD_COMMAND_RESPONSE_H
#define SENSORREAD_COMMAND_RESPONSE_H
#include "response.h"
#include "globals/enums.h"

using namespace Sensor_Module;
class SensorRead_Command_Response : public Response
{
public:
    SensorRead_Command_Response();
    SensorRead_Command_Response(int cmdId, SensorType type, CommunicateCoreUnderlying::PressureSensorDeviceID deviceId, qint32 curPressure, QString key = "");
public:
    inline CommunicateCoreUnderlying::PressureSensorDeviceID deviceId()const{return _deviceId;}
    inline SensorType type()const{return _type;}
    inline qint32 curPressure()const{return _curPressure;}
private:
    CommunicateCoreUnderlying::PressureSensorDeviceID _deviceId;
    qint32 _curPressure;
    SensorType _type;
};
Q_DECLARE_METATYPE(SensorRead_Command_Response)
#endif // SENSORREAD_COMMAND_RESPONSE_H
