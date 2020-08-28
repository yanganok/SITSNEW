#ifndef XYINIT_COMMAND_RESPONSE_H
#define XYINIT_COMMAND_RESPONSE_H
#include "response.h"

class XYInit_Command_Response : public Response
{
public:
public:
    XYInit_Command_Response();
    XYInit_Command_Response(int cmdId, CommunicateCoreUnderlying::XYStageDeviceId deviceId, CommunicateCoreUnderlying::XYStageStatusWord status);
public:
    inline CommunicateCoreUnderlying::XYStageDeviceId deviceId()const{return _deviceId;}
    inline CommunicateCoreUnderlying::XYStageStatusWord status()const{return _status;}
private:
    CommunicateCoreUnderlying::XYStageDeviceId _deviceId;
    CommunicateCoreUnderlying::XYStageStatusWord _status;
};
Q_DECLARE_METATYPE(XYInit_Command_Response)
#endif // XYINIT_COMMAND_RESPONSE_H
