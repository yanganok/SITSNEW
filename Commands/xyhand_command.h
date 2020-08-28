#ifndef XYHAND_COMMAND_H
#define XYHAND_COMMAND_H
#include "command.h"
/**
* @projectName   SITS
* @brief         xy平台握手
* @author        YangAn
* @date          2020-08-13
* @Email         yangan@AutoBio.com.cn
*/
class XYHand_Command : public Command
{
    Q_OBJECT
public:
    XYHand_Command();
    /**
     * @brief XYHand_Command    xy平台握手命令
     * @param operate           所依附的operate
     * @param response          响应信息
     * @param msec              超时时间，设为-1则没有超时
     * @param deviceId          设备号
     */
    XYHand_Command(InstrumentOperator* operate,  Response *response, int msec, CommunicateCoreUnderlying::XYStageDeviceId deviceId);
public:
    void receiveResponse(QByteArray pkg) override;
    /**
     * @brief deviceId  设备号
     * @return          返回设备号
     */
    inline CommunicateCoreUnderlying::XYStageDeviceId deviceId()const{return _deviceId;}
protected:
    bool package(QByteArray& arr) override;
    bool packageToResponse(QByteArray& arr) override;
private:
    CommunicateCoreUnderlying::XYStageDeviceId _deviceId;
};

#endif // XYHAND_COMMAND_H
