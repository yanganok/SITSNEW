#ifndef PUMPABSORB_COMMAND_RESPONSE_H
#define PUMPABSORB_COMMAND_RESPONSE_H
#include "response.h"

class PumpAbsorb_Command_Response : public Response
{
public:
    PumpAbsorb_Command_Response();
    PumpAbsorb_Command_Response(int cmdId, CommunicateCoreUnderlying::SyringPumpId deviceId, quint32 curPos, QString key = "");
public:
    inline CommunicateCoreUnderlying::SyringPumpId deviceId()const{return _deviceId;}
    inline quint32 curPos()const{return _curPos;}
private:
    CommunicateCoreUnderlying::SyringPumpId _deviceId;
    quint32 _curPos;
};
Q_DECLARE_METATYPE(PumpAbsorb_Command_Response)

#endif // PUMPABSORB_COMMAND_RESPONSE_H
