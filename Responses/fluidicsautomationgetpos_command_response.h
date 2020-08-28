#ifndef FLUIDICSAUTOMATIONGETPOS_COMMAND_RESPONSE_H
#define FLUIDICSAUTOMATIONGETPOS_COMMAND_RESPONSE_H
#include "response.h"
#include "globals/enums.h"
using namespace Fluidics_Module;
class FluidicsAutomationGetPos_Command_Response:Response
{
public:
    FluidicsAutomationGetPos_Command_Response();
    FluidicsAutomationGetPos_Command_Response(FluidicsAutomationPosition pos, QString raw);
public:
    inline FluidicsAutomationPosition pos()const{return _pos;}
    inline QString raw()const{return _raw;}
private:
    FluidicsAutomationPosition _pos;
    QString _raw;
};
Q_DECLARE_METATYPE(FluidicsAutomationGetPos_Command_Response)
#endif // FLUIDICSAUTOMATIONGETPOS_COMMAND_RESPONSE_H
