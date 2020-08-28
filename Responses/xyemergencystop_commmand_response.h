#ifndef XYEMERGENCYSTOP_COMMMAND_RESPONSE_H
#define XYEMERGENCYSTOP_COMMMAND_RESPONSE_H
#include "response.h"

class XYEmergencyStop_Commmand_Response : public Response
{
public:
    XYEmergencyStop_Commmand_Response();
    XYEmergencyStop_Commmand_Response(int cmdId, CommunicateCoreUnderlying::XYStageDeviceId deviceId, CommunicateCoreUnderlying::XYStageStatusWord status);
public:
    inline CommunicateCoreUnderlying::XYStageDeviceId deviceId()const{return _deviceId;}
    inline CommunicateCoreUnderlying::XYStageStatusWord status()const{return _status;}
private:
    CommunicateCoreUnderlying::XYStageDeviceId _deviceId;
    CommunicateCoreUnderlying::XYStageStatusWord _status;
};
Q_DECLARE_METATYPE(XYEmergencyStop_Commmand_Response)

#endif // XYEMERGENCYSTOP_COMMMAND_RESPONSE_H
