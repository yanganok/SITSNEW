#ifndef PRESSURESENSORREAD_COMMAND_RESPONSE_H
#define PRESSURESENSORREAD_COMMAND_RESPONSE_H
#include "response.h"

class PressureSensorRead_Command_Response : public Response
{
public:
    PressureSensorRead_Command_Response();
    PressureSensorRead_Command_Response(int volts);
public:
    inline int volts()const{return _volts;}
private:
    int _volts;
};
Q_DECLARE_METATYPE(PressureSensorRead_Command_Response)
#endif // PRESSURESENSORREAD_COMMAND_RESPONSE_H
