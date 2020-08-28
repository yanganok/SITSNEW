#ifndef SENSOROVERRIDE_COMMAND_H
#define SENSOROVERRIDE_COMMAND_H
#include "command.h"
#include "globals/enums.h"

using namespace Sensor_Module;
class SensorOverride_Command : public Command
{
    Q_OBJECT
public:
    SensorOverride_Command();
    SensorOverride_Command(InstrumentOperator* operate,  Response *response, int msec, SensorType type,  bool clear, bool state);
public:
    inline SensorType type()const{return _type;}
    inline bool clear()const{return _clear;}
    inline bool state()const{return _state;}
protected:
    bool package(QByteArray& arr) override;
    bool packageToResponse(QByteArray& arr) override;
private:
    SensorType _type;
    bool _clear;
    bool _state;
};

#endif // SENSOROVERRIDE_COMMAND_H
