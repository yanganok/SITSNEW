#ifndef SENSORNOTIFY_COMMAND_RESPONSE_H
#define SENSORNOTIFY_COMMAND_RESPONSE_H
#include "response.h"
#include "globals/enums.h"

using namespace Sensor_Module;
class SensorNotify_Command_Response : public Response
{
public:
    SensorNotify_Command_Response();
    SensorNotify_Command_Response(Sensor_Module::SensorType type, bool state);
public:
    inline SensorType type()const{return _type;}
    inline bool state()const{return _state;}
private:
    SensorType _type;
    bool _state;
};
Q_DECLARE_METATYPE(SensorNotify_Command_Response)
#endif // SENSORNOTIFY_COMMAND_RESPONSE_H
