#ifndef XYMOVETOHOMEPOINT_COMMAND_H
#define XYMOVETOHOMEPOINT_COMMAND_H
#include "command.h"
/**
* @projectName   SITS
* @brief         xy随动到Home点
* @author        YangAn
* @date          2020-08-13
* @Email         yangan@AutoBio.com.cn
*/
class XYMoveToHomePoint_Command : public Command
{
    Q_OBJECT
public:
    XYMoveToHomePoint_Command();
    /**
     * @brief XYMoveToHomePoint_Command xy随动到Home点命令
     * @param operate                   所依附的operate
     * @param response                  响应信息
     * @param msec                      超时时间，设为-1则没有超时
     * @param deviceId                  设备号
     */
    XYMoveToHomePoint_Command(InstrumentOperator* operate,  Response *response, int msec, CommunicateCoreUnderlying::XYStageDeviceId deviceId, QString key = "", bool async = false, int delayMs = 0);
public:
    void receiveResponse(QByteArray pkg) override;
    /**
     * @brief deviceId                  设备号
     * @return                          返回设备号
     */
    inline CommunicateCoreUnderlying::XYStageDeviceId deviceId()const{return _deviceId;}
protected:
    bool package(QByteArray& arr) override;
    bool packageToResponse(QByteArray& arr) override;
private:
    CommunicateCoreUnderlying::XYStageDeviceId _deviceId;
};

#endif // XYMOVETOHOMEPOINT_COMMAND_H
