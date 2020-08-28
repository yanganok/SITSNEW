#ifndef XYFINDZERO_COMMAND_H
#define XYFINDZERO_COMMAND_H
#include "command.h"
/**
 * @brief The XYFindZero_Command class xy寻零点
 */
class XYFindZero_Command : public Command
{
    Q_OBJECT
public:
    XYFindZero_Command();
    XYFindZero_Command(InstrumentOperator* operate,  Response *response, int msec, CommunicateCoreUnderlying::XYStageDeviceId deviceId, bool isXFindZero, bool isYFindZero);
public:
    void receiveResponse(QByteArray pkg) override;
    inline CommunicateCoreUnderlying::XYStageDeviceId deviceId()const{return _deviceId;}
protected:
    bool package(QByteArray& arr) override;
    bool packageToResponse(QByteArray& arr) override;
private:
    CommunicateCoreUnderlying::XYStageDeviceId _deviceId;
    bool _isXFindZero;
    bool _isYFindZero;
};

#endif // XYFINDZERO_COMMAND_H
