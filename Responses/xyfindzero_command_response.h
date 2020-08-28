#ifndef XYFINDZERO_COMMAND_RESPONSE_H
#define XYFINDZERO_COMMAND_RESPONSE_H
#include "Responses/response.h"

class XYFindZero_Command_Response : public Response
{
public:
    XYFindZero_Command_Response();
    XYFindZero_Command_Response(int cmdId, CommunicateCoreUnderlying::XYStageDeviceId deviceId, CommunicateCoreUnderlying::XYStageStatusWord status, bool isXFindZero, bool isYFindZero);
public:
    inline CommunicateCoreUnderlying::XYStageDeviceId deviceId()const{return _deviceId;}
    inline CommunicateCoreUnderlying::XYStageStatusWord status()const{return _status;}
    inline bool isXFindZero()const{return _isXFindZero;}
    inline bool isYFindZero()const{return _isYFindZero;}
private:
    CommunicateCoreUnderlying::XYStageDeviceId _deviceId;
    CommunicateCoreUnderlying::XYStageStatusWord _status;
    bool _isXFindZero;
    bool _isYFindZero;
};
Q_DECLARE_METATYPE(XYFindZero_Command_Response)

#endif // XYFINDZERO_COMMAND_RESPONSE_H
