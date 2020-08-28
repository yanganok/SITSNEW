#ifndef PUMPINIT_COMMAND_H
#define PUMPINIT_COMMAND_H
#include "command.h"
#include "pump_command.h"
/**
* @brief The PumpInit_Command class 泵初始化
*/
class PumpInit_Command : public Pump_Command
{
public:
    PumpInit_Command();
    /**
     * @brief PumpInit_Command
     * @param operate   所属操作者
     * @param response  相应信息(设置nullptr即可)
     * @param msec      超时时间(毫秒)
     * @param _deviceId 设备ID
     */
    PumpInit_Command(InstrumentOperator* operate,  Response *response, int msec = -1, CommunicateCoreUnderlying::SyringPumpId _deviceId = CommunicateCoreUnderlying::SyringPumpId::ALL, QString key = "", bool async = false, int delayMs = 0 );
protected:
    bool package(QByteArray &arr) override;
    bool packageToResponse(QByteArray &arr) override;
public:
    void receiveResponse(QByteArray pkg) override;
private:
    CommunicateCoreUnderlying::SyringPumpId _deviceId;
};

#endif // PUMPINIT_COMMAND_H
