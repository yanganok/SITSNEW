#ifndef XYEMERGENCYSTOP_COMMMAND_H
#define XYEMERGENCYSTOP_COMMMAND_H

#include <QObject>
#include "command.h"
/**
 * @brief The XYEmergencyStop_Commmand class xy平台急停
 */
class XYEmergencyStop_Commmand : public Command
{
    Q_OBJECT
public:
    XYEmergencyStop_Commmand();
    XYEmergencyStop_Commmand(InstrumentOperator* operate,  Response *response, int msec, CommunicateCoreUnderlying::XYStageDeviceId deviceId);
public:
    void receiveResponse(QByteArray pkg) override;
    inline CommunicateCoreUnderlying::XYStageDeviceId deviceId()const{return _deviceId;}
protected:
    bool package(QByteArray& arr) override;
    bool packageToResponse(QByteArray& arr) override;
private:
    CommunicateCoreUnderlying::XYStageDeviceId _deviceId;
};

#endif // XYEMERGENCYSTOP_COMMMAND_H
