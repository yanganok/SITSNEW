#ifndef VALVEINIT_COMMAND_H
#define VALVEINIT_COMMAND_H
#include "command.h"

class ValveInit_Command : public Command
{
    Q_OBJECT
public:
    ValveInit_Command();
    ValveInit_Command(InstrumentOperator* operate,  Response *response, int msec, CommunicateCoreUnderlying::ValveDeviceId deviceId, QString key = "", bool async = false, int delayMs = 0);
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

#endif // VALVEINIT_COMMAND_H
