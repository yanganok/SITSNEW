#include "pumpinit_command.h"
#include "Responses/pumpinit_command_response.h"

PumpInit_Command::PumpInit_Command()
{
    _typeName = classtype();
}

PumpInit_Command::PumpInit_Command(InstrumentOperator *operate, Response *response, int msec, CommunicateCoreUnderlying::SyringPumpId deviceId, QString key, bool async, int delayMs)
    :Pump_Command(operate, response, msec, key, async, delayMs), _deviceId(deviceId)
{
    _typeName = classtype();
}

bool PumpInit_Command::package(QByteArray &arr)
{
    arr = Command::toPackage(static_cast<quint8>(CommunicateCoreUnderlying::CommandType::SEND),
                static_cast<quint8>(CommunicateCoreUnderlying::DevicType::DE_TP_SYRINGE),
                static_cast<quint8>(_deviceId),
                static_cast<quint8>(CommunicateCoreUnderlying::SyringPumpControlWord::CW_SYRINGE_INIT),
                QVector<quint32>()
                );
    Command::package(arr);
    return true;
}

bool PumpInit_Command::packageToResponse(QByteArray &arr)
{
    int code;
    code = BytesToAny::toInt((quint8 *)arr.data() + 3);
    _curPos = 0;
    if(*(arr.data() + 9) == (quint8)CommunicateCoreUnderlying::SyringPumpControlWord::CW_SYRINGE_INIT)
    {
        CommunicateCoreUnderlying::SyringPumpStatusWord status = static_cast<CommunicateCoreUnderlying::SyringPumpStatusWord>(BytesToAny::toQUint16((quint8 *)arr.data() + 11));
        CommunicateCoreUnderlying::SyringPumpId deviceId = static_cast<CommunicateCoreUnderlying::SyringPumpId>(*((quint8 *)arr.data() + 8));
        std::shared_ptr<PumpInit_Command_Response> response(new PumpInit_Command_Response(code, deviceId, status, _curPos));
        emit translateResponseToOperator(response);
        Command::packageToResponse(arr);
    }
    return true;
}

void PumpInit_Command::receiveResponse(QByteArray pkg)
{
    packageToResponse(pkg);
}
