#ifndef VALVEINIT_COMMAND_RESPONSE_H
#define VALVEINIT_COMMAND_RESPONSE_H
#include "response.h"

class ValveInit_Command_Response : public Response
{
public:
    ValveInit_Command_Response();
    ValveInit_Command_Response(int cmdId, CommunicateCoreUnderlying::ValveDeviceId deviceId, CommunicateCoreUnderlying::ValveStatusWord statusCode, QString key = "");
public:
    int cmdId()const{return _cmdId;}
    CommunicateCoreUnderlying::ValveDeviceId deviceId()const{return _deviceId;}
    CommunicateCoreUnderlying::ValveStatusWord statusCode()const{return _statusCode;}
private:
    CommunicateCoreUnderlying::ValveDeviceId _deviceId;
    CommunicateCoreUnderlying::ValveStatusWord _statusCode;
};
Q_DECLARE_METATYPE(ValveInit_Command_Response)


#endif // VALVEINIT_COMMAND_RESPONSE_H
