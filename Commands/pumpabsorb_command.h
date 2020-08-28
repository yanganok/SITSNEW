#ifndef PUMPABSORB_COMMAND_H
#define PUMPABSORB_COMMAND_H

#include <QObject>
#include "pump_command.h"
#include "Responses/pumpabsorb_command_response.h"
/**
 * @brief The PumpAbsorb_Command class 泵吸命令
 */
class PumpAbsorb_Command : public Pump_Command
{
    Q_OBJECT
public:
    PumpAbsorb_Command();
    /**
     * @brief PumpAbsorb_Command
     * @param operate   所属操作者
     * @param response  相应信息(设置nullptr即可)
     * @param msec      超时时间(毫秒)
     * @param deviceId  设备号
     * @param valveId   对应阀号
     * @param pumpSpeed 泵的速度(ul/min)
     * @param volumn    吸的体积(ul)
     */
    PumpAbsorb_Command(InstrumentOperator *operate, Response *response, int msec, CommunicateCoreUnderlying::SyringPumpId deviceId, quint16 valveId, quint16 pumpSpeed, qint16 volumn, QString key = "", bool async = false, int delayMs = 0);
protected:
    bool package(QByteArray& arr) override;
    bool packageToResponse(QByteArray &arr) override;
public:
    void receiveResponse(QByteArray pkg) override;
private:
    CommunicateCoreUnderlying::SyringPumpId _deviceId;
    quint16 _valveId;
    quint16 _pumpSpeed;
    qint16 _volumn;
};

#endif // PUMPABSORB_COMMAND_H
