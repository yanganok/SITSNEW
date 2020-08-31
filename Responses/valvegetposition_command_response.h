#ifndef VALVEGETPOSITION_COMMAND_RESPONSE_H
#define VALVEGETPOSITION_COMMAND_RESPONSE_H
#include "response.h"

class ValveGetPosition_Command_Response : public Response
{
public:
    ValveGetPosition_Command_Response();
    ValveGetPosition_Command_Response(int cmdId, CommunicateCoreUnderlying::ValveDeviceId deviceId, int curPos, QString key = "");
public:
    int cmdId()const{return _cmdId;}
    CommunicateCoreUnderlying::ValveDeviceId deviceId()const{return _deviceId;}
    int curPos()const{return _curPos;}
private:
    CommunicateCoreUnderlying::ValveDeviceId _deviceId;
    int _curPos;
};
Q_DECLARE_METATYPE(ValveGetPosition_Command_Response)

#endif // VALVEGETPOSITION_COMMAND_RESPONSE_H
