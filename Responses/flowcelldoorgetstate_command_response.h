#ifndef FLOWCELLDOORGETSTATE_COMMAND_RESPONSE_H
#define FLOWCELLDOORGETSTATE_COMMAND_RESPONSE_H
#include "response.h"
#include "globals/enums.h"
using namespace Flowcell_Module;
class FlowcellDoorGetState_Command_Response : public Response
{
public:
    FlowcellDoorGetState_Command_Response();
    FlowcellDoorGetState_Command_Response(FlowcellDoorState state);
public:
    inline FlowcellDoorState state()const{return _state;}
private:
    FlowcellDoorState _state;
};
Q_DECLARE_METATYPE(FlowcellDoorGetState_Command_Response)
#endif // FLOWCELLDOORGETSTATE_COMMAND_RESPONSE_H
