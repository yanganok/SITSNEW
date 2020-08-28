#ifndef PUMPINIT_COMMAND_RESPONSE_H
#define PUMPINIT_COMMAND_RESPONSE_H
#include "response.h"

class PumpInit_Command_Response : public Response
{
public:
    PumpInit_Command_Response();
    PumpInit_Command_Response(int cmdId, CommunicateCoreUnderlying::SyringPumpId deviceId,  CommunicateCoreUnderlying::SyringPumpStatusWord statusCode, int curPos, QString key = "");
public:
    inline CommunicateCoreUnderlying::SyringPumpStatusWord status()const{return _statusCode;}
    inline CommunicateCoreUnderlying::SyringPumpId deviceId()const{return _deviceId;}
    inline int curPos()const{return _curPos;}
private:
    CommunicateCoreUnderlying::SyringPumpId _deviceId;
    CommunicateCoreUnderlying::SyringPumpStatusWord _statusCode;
    int _curPos;
};
Q_DECLARE_METATYPE(PumpInit_Command_Response)

#endif // PUMPINIT_COMMAND_RESPONSE_H
