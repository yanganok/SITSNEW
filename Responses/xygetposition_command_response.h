#ifndef XYGETPOSITION_COMMAND_RESPONSE_H
#define XYGETPOSITION_COMMAND_RESPONSE_H
#include "response.h"

class XYGetPosition_Command_Response : public Response
{
public:
    XYGetPosition_Command_Response();
    XYGetPosition_Command_Response(int cmdId, CommunicateCoreUnderlying::XYStageDeviceId deviceId, int xPos, int yPos, CommunicateCoreUnderlying::XYStageStatusWord status);
public:
    /**
     * @brief deviceId
     * @return xy平台设备号
     */
    inline CommunicateCoreUnderlying::XYStageDeviceId deviceId()const{return _deviceId;}
    /**
     * @brief status
     * @return xy平台状态字
     */
    inline CommunicateCoreUnderlying::XYStageStatusWord status()const{return _status;}
    /**
     * @brief xPos
     * @return x位置（单位：3um）
     */
    inline int xPos()const{return _xPos;}
    /**
     * @brief yPos
     * @return y位置（单位：3um）
     */
    inline int yPos()const{return _yPos;}
private:
    CommunicateCoreUnderlying::XYStageDeviceId _deviceId;
    CommunicateCoreUnderlying::XYStageStatusWord _status;
    int _xPos;
    int _yPos;
};
Q_DECLARE_METATYPE(XYGetPosition_Command_Response)
#endif // XYGETPOSITION_COMMAND_RESPONSE_H
