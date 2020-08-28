#ifndef XYMOVETO_COMMAND_RESPONSE_H
#define XYMOVETO_COMMAND_RESPONSE_H
#include "response.h"
/**
* @projectName   SITS
* @brief         XY移动返回结果
* @author        YangAn
* @date          2020-08-12
* @Email         yangan@AutoBio.com.cn
*/
class XYMoveTo_Command_Response : public Response
{
public:
    XYMoveTo_Command_Response();
    XYMoveTo_Command_Response(int cmdId, CommunicateCoreUnderlying::XYStageDeviceId deviceId, int xPos, int yPos, CommunicateCoreUnderlying::XYStageStatusWord status);
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
Q_DECLARE_METATYPE(XYMoveTo_Command_Response)
#endif // XYMOVETO_COMMAND_RESPONSE_H
