#ifndef XYMOVETOHOMEPOINT_COMMAND_RESPONSE_H
#define XYMOVETOHOMEPOINT_COMMAND_RESPONSE_H
#include "response.h"

class XYMoveToHomePoint_Command_Response : public Response
{
public:
    XYMoveToHomePoint_Command_Response();
    XYMoveToHomePoint_Command_Response(int cmdId, CommunicateCoreUnderlying::XYStageDeviceId deviceId, CommunicateCoreUnderlying::XYStageStatusWord status);
public:
    inline CommunicateCoreUnderlying::XYStageDeviceId deviceId()const{return _deviceId;}
    inline CommunicateCoreUnderlying::XYStageStatusWord status()const{return _status;}
private:
    CommunicateCoreUnderlying::XYStageDeviceId _deviceId;
    CommunicateCoreUnderlying::XYStageStatusWord _status;
};
Q_DECLARE_METATYPE(XYMoveToHomePoint_Command_Response)

#endif // XYMOVETOHOMEPOINT_COMMAND_RESPONSE_H
