#ifndef FLOWCELLDOORGETSEALDISTANCE_COMMAND_RESPONSE_H
#define FLOWCELLDOORGETSEALDISTANCE_COMMAND_RESPONSE_H
#include "response.h"

class FlowcellDoorGetSealDistance_Command_Response : public Response
{
public:
    FlowcellDoorGetSealDistance_Command_Response();
    FlowcellDoorGetSealDistance_Command_Response(quint32 steps);
public:
    inline quint32 steps()const{return _steps;}
private:
    quint32 _steps;
};
Q_DECLARE_METATYPE(FlowcellDoorGetSealDistance_Command_Response)

#endif // FLOWCELLDOORGETSEALDISTANCE_COMMAND_RESPONSE_H
