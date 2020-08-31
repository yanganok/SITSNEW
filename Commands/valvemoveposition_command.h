#ifndef VALVEMOVEPOSITION_COMMAND_H
#define VALVEMOVEPOSITION_COMMAND_H
#include "command.h"

class ValveMovePosition_Command : public Command
{
    Q_OBJECT
public:
    ValveMovePosition_Command();
    ValveMovePosition_Command(InstrumentOperator* operate,  Response *response, int msec, CommunicateCoreUnderlying::ValveDeviceId deviceId, qint16 pos, QString key = "", bool async = false, int delayMs = 0);
public:
    inline CommunicateCoreUnderlying::ValveDeviceId deviceId()const{return _deviceId;}
protected:
    bool package(QByteArray& arr) override;
    bool packageToResponse(QByteArray& arr) override;
public:
    void receiveResponse(QByteArray pkg) override;
    inline qint16 pos()const{return  _pos;}
private:
    CommunicateCoreUnderlying::ValveDeviceId _deviceId;
    qint16 _pos;
};

#endif // VALVEMOVEPOSITION_COMMAND_H
