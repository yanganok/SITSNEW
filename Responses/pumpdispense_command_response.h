#ifndef PUMPDISPENSE_COMMAND_RESPONSE_H
#define PUMPDISPENSE_COMMAND_RESPONSE_H
#include "response.h"

class PumpDispense_Command_Response : public Response
{
public:
    PumpDispense_Command_Response();
    PumpDispense_Command_Response(int cmdId, CommunicateCoreUnderlying::SyringPumpId deviceId, quint32 curPos, QString key = "");
public:
    inline CommunicateCoreUnderlying::SyringPumpId deviceId()const{return _deviceId;}
    inline quint32 curPos()const{return _curPos;}
private:
    CommunicateCoreUnderlying::SyringPumpId _deviceId;
    quint32 _curPos;
};
Q_DECLARE_METATYPE(PumpDispense_Command_Response)


#endif // PUMPDISPENSE_COMMAND_RESPONSE_H
