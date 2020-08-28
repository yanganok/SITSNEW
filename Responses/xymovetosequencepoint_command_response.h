#ifndef XYMOVETOSEQUENCEPOINT_COMMAND_RESPONSE_H
#define XYMOVETOSEQUENCEPOINT_COMMAND_RESPONSE_H
#include "response.h"

class XYMoveToSequencePoint_Command_Response : public Response
{
public:
    XYMoveToSequencePoint_Command_Response();
    XYMoveToSequencePoint_Command_Response(int cmdId, CommunicateCoreUnderlying::XYStageDeviceId deviceId, CommunicateCoreUnderlying::XYStageStatusWord status);
public:
    inline CommunicateCoreUnderlying::XYStageDeviceId deviceId()const{return _deviceId;}
    inline CommunicateCoreUnderlying::XYStageStatusWord status()const{return _status;}
private:
    CommunicateCoreUnderlying::XYStageDeviceId _deviceId;
    CommunicateCoreUnderlying::XYStageStatusWord _status;
};
Q_DECLARE_METATYPE(XYMoveToSequencePoint_Command_Response)
#endif // XYMOVETOSEQUENCEPOINT_COMMAND_RESPONSE_H
