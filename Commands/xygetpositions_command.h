#ifndef XYGETPOSITIONS_COMMAND_H
#define XYGETPOSITIONS_COMMAND_H
#include "command.h"

/**
* @projectName   SITS
* @brief         xy平台获取绝对位置(单位3um)
* @author        YangAn
* @date          2020-08-13
* @Email         yangan@AutoBio.com.cn
*/
class XYGetPositions_Command : public Command
{
    Q_OBJECT
public:
    XYGetPositions_Command();
    /**
     * @brief XYGetPositions_Command    xy平台获取绝对位置命令
     * @param operate                   所依附的operate
     * @param response                  响应信息
     * @param msec                      超时时间，设为-1则没有超时
     * @param deviceId                  设备号
     * @param xPos                      x方向位置
     * @param yPos                      y方向位置
     */
    XYGetPositions_Command(InstrumentOperator* operate,  Response *response, int msec, CommunicateCoreUnderlying::XYStageDeviceId deviceId, int xPos, int yPos);
public:
    void receiveResponse(QByteArray pkg) override;
    /**
     * @brief deviceId  设备号
     * @return          返回设备号
     */
    inline CommunicateCoreUnderlying::XYStageDeviceId deviceId()const{return _deviceId;}
    /**
     * @brief xPos      x绝对位置
     * @return          返回x绝对位置
     */
    inline int xPos()const{return _xPos;}
    /**
     * @brief yPos      y绝对位置
     * @return          返回y绝对位置
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

#endif // XYGETPOSITIONS_COMMAND_H
