#ifndef VALVEMOVEPOSITION_COMMAND_RESPONSE_H
#define VALVEMOVEPOSITION_COMMAND_RESPONSE_H
#include "response.h"

class ValveMovePosition_Command_Response : public Response
{
public:
    ValveMovePosition_Command_Response();
    ValveMovePosition_Command_Response(int cmdId, CommunicateCoreUnderlying::ValveDeviceId deviceId, int curPos, QString key = "");
public:
    int cmdId()const{return _cmdId;}
    CommunicateCoreUnderlying::ValveDeviceId deviceId()const{return _deviceId;}
    int curPos()const{return _curPos;}
private:
    CommunicateCoreUnderlying::ValveDeviceId _deviceId;
    int _curPos;
};
Q_DECLARE_METATYPE(ValveMovePosition_Command_Response)

#endif // VALVEMOVEPOSITION_COMMAND_RESPONSE_H
