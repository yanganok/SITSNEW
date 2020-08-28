#ifndef XYMOVETO_COMMAND_H
#define XYMOVETO_COMMAND_H
#include "command.h"
/**
* @projectName   SITS
* @brief         XYMoveTo_Command class xy移动绝对位置：x(-5800, 8750), y(500, 46000)
* @author        YangAn
* @date          2020-08-13
* @Email         yangan@AutoBio.com.cn
*/
class XYMoveTo_Command : public Command
{
    Q_OBJECT
public:
    XYMoveTo_Command();
    /**
     * @brief XYMoveTo_Command xy平台移动到绝对位置，单位为（3um）
     * @param operate          所依附的operate
     * @param response         响应信息
     * @param msec             超时时间，设为-1则没有超时
     * @param deviceId         设备号
     * @param xPos             x方向位置
     * @param yPos             y方向位置
     */
    XYMoveTo_Command(InstrumentOperator* operate,  Response *response, int msec, CommunicateCoreUnderlying::XYStageDeviceId deviceId, int xPos, int yPos, QString key = "", bool async = false, int delayMs = 0);
public:
    void receiveResponse(QByteArray pkg) override;
    /**
     * @brief deviceId  设备号
     * @return          返回设备号
     */
    inline CommunicateCoreUnderlying::XYStageDeviceId deviceId()const{return _deviceId;}
    /**
     * @brief xPos      x方向位置
     * @return          返回x方向位置
     */
    inline int xPos()const{return _xPos;}
    /**
     * @brief yPos     y方向位置
     * @return         返回y方向位置
     */
    inline int yPos()const{return _yPos;}
protected:
    bool package(QByteArray& arr) override;
    bool packageToResponse(QByteArray& arr) override;
private:
    int _xPos;
    int _yPos;
private:
    CommunicateCoreUnderlying::XYStageDeviceId _deviceId;
};

#endif // XYMOVETO_COMMAND_H
