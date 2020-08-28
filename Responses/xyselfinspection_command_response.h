#ifndef XYSELFINSPECTION_COMMAND_RESPONSE_H
#define XYSELFINSPECTION_COMMAND_RESPONSE_H
#include "response.h"

class XYSelfInspection_Command_Response : public Response
{
public:
    XYSelfInspection_Command_Response();
    XYSelfInspection_Command_Response(int cmdId, CommunicateCoreUnderlying::XYStageDeviceId deviceId, CommunicateCoreUnderlying::XYStageStatusWord status);
public:
    inline CommunicateCoreUnderlying::XYStageDeviceId deviceId()const{return _deviceId;}
    inline CommunicateCoreUnderlying::XYStageStatusWord status()const{return _status;}
private:
    CommunicateCoreUnderlying::XYStageDeviceId _deviceId;
    CommunicateCoreUnderlying::XYStageStatusWord _status;
};
Q_DECLARE_METATYPE(XYSelfInspection_Command_Response)
#endif // XYSELFINSPECTION_COMMAND_RESPONSE_H
