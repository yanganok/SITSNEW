#ifndef XYHAND_COMMAND_RESPONSE_H
#define XYHAND_COMMAND_RESPONSE_H
#include "response.h"

class XYHand_Command_Response : public Response
{
public:
    XYHand_Command_Response();
    XYHand_Command_Response(int cmdId, CommunicateCoreUnderlying::XYStageDeviceId deviceId, CommunicateCoreUnderlying::XYStageStatusWord status);
public:
    inline CommunicateCoreUnderlying::XYStageDeviceId deviceId()const{return _deviceId;}
    inline CommunicateCoreUnderlying::XYStageStatusWord status()const{return _status;}
private:
    CommunicateCoreUnderlying::XYStageDeviceId _deviceId;
    CommunicateCoreUnderlying::XYStageStatusWord _status;
};
Q_DECLARE_METATYPE(XYHand_Command_Response)
#endif // XYHAND_COMMAND_RESPONSE_H
