#ifndef VALVEGETPOSITION_COMMAND_H
#define VALVEGETPOSITION_COMMAND_H
#include "command.h"
/**
* @projectName   SITS
* @brief         获取阀当前位置
* @author        YangAn
* @date          2020-08-28
* @Email         yangan@AutoBio.com.cn
*/
class ValveGetPosition_Command : public Command
{
    Q_OBJECT
public:
    ValveGetPosition_Command();
    ValveGetPosition_Command(InstrumentOperator* operate,  Response *response, int msec, CommunicateCoreUnderlying::ValveDeviceId deviceId, QString key = "", bool async = false, int delayMs = 0);
public:
    inline CommunicateCoreUnderlying::ValveDeviceId deviceId()const{return _deviceId;}
protected:
    bool package(QByteArray& arr) override;
    bool packageToResponse(QByteArray& arr) override;
public:
    void receiveResponse(QByteArray pkg) override;
private:
    CommunicateCoreUnderlying::ValveDeviceId _deviceId;
};

#endif // VALVEGETPOSITION_COMMAND_H
