#ifndef SENSORREAD_COMMAND_H
#define SENSORREAD_COMMAND_H
#include "command.h"
#include "globals/enums.h"

using namespace Sensor_Module;
class SensorRead_Command : public Command
{
    Q_OBJECT
public:
    SensorRead_Command();
    SensorRead_Command(InstrumentOperator* operate,  Response *response, int msec, SensorType type, CommunicateCoreUnderlying::PressureSensorDeviceID deviceId, QString key = "", bool async = false, int delayMs = 0);
public:
    inline SensorType type()const{return _type;}
    inline CommunicateCoreUnderlying::PressureSensorDeviceID deviceId()const{return _deviceId;}
protected:
    bool package(QByteArray& arr) override;
    bool packageToResponse(QByteArray& arr) override;
public:
    void receiveResponse(QByteArray pkg) override;
private:
    SensorType _type;
    CommunicateCoreUnderlying::PressureSensorDeviceID _deviceId;
};

#endif // SENSORREAD_COMMAND_H
