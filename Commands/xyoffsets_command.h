#ifndef XYOFFSETS_COMMAND_H
#define XYOFFSETS_COMMAND_H
#include "command.h"
/**
 * @brief The XYOffsets_Command class 该类不用
 */
class XYOffsets_Command : public Command
{
public:
    XYOffsets_Command();
    XYOffsets_Command(InstrumentOperator* operate,  Response *response, int msec, CommunicateCoreUnderlying::BubbleDeviceId deviceId, int x_nm, int y_nm, QString key = "", bool async = false, int delayMs = 0);
public:
    void receiveResponse(QByteArray pkg) override;
    inline int x_nm()const{return _x_nm;}
    inline int y_nm()const{return _y_nm;}
protected:
    bool package(QByteArray& arr) override;
    bool packageToResponse(QByteArray& arr) override;
private:
    int _x_nm;
    int _y_nm;
    CommunicateCoreUnderlying::BubbleDeviceId _deviceId;
};

#endif // XYOFFSETS_COMMAND_H
