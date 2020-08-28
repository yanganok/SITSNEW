#include "pumpdispense_command.h"
#include "Responses/pumpdispense_command_response.h"

PumpDispense_Command::PumpDispense_Command()
{
    _typeName = classtype();
}

PumpDispense_Command::PumpDispense_Command(InstrumentOperator *operate, Response *response, int msec, CommunicateCoreUnderlying::SyringPumpId deviceId, quint16 valveId, quint16 pumpSpeed, qint16 volumn, QString key, bool async, int delayMs)
    :Pump_Command(operate, response, msec, key, async, delayMs),_valveId(valveId), _pumpSpeed(pumpSpeed), _volumn(volumn), _deviceId(deviceId)
{
    _typeName = classtype();
}

bool PumpDispense_Command::package(QByteArray &arr)
{
    arr = Command::toPackage(static_cast<quint8>(CommunicateCoreUnderlying::CommandType::SEND),
                static_cast<quint8>(CommunicateCoreUnderlying::DevicType::DE_TP_SYRINGE),
                static_cast<quint8>(_deviceId),
                static_cast<quint8>(CommunicateCoreUnderlying::SyringPumpControlWord::CW_SYRINGE_MOVE),
                QVector<quint16>{static_cast<quint16>(_valveId),
                                 static_cast<quint16>(qRound(_pumpSpeed * Fluidics_Module::stepsPerUl * 0.016666666666666666 * 2)),
                                 static_cast<quint16>(_curPos / Fluidics_Module::stepsPerUl - _volumn < 0?0:_curPos / Fluidics_Module::stepsPerUl - _volumn)}
                );
    Command::package(arr);
    return true;
}

bool PumpDispense_Command::packageToResponse(QByteArray &arr)
{
    CommunicateCoreUnderlying::SyringPumpId deviceId;
    int code;
    quint16 bubbleCode;
    quint32 bubbleIntervalus;
    code = BytesToAny::toInt((quint8 *)arr.data() + 3);
    if(*(arr.data() + 9) == (quint8)CommunicateCoreUnderlying::SyringPumpControlWord::CW_SYRINGE_MOVE)
    {
        deviceId = static_cast<CommunicateCoreUnderlying::SyringPumpId>(*(arr.data() + 8));
        _curPos = BytesToAny::toQInt16((quint8 *)arr.data() + 11);
        std::shared_ptr<PumpDispense_Command_Response> response(new PumpDispense_Command_Response(code, deviceId, _curPos, _key));
        emit translateResponseToOperator(response);
        Command::packageToResponse(arr);
    }
    return true;
}

void PumpDispense_Command::receiveResponse(QByteArray pkg)
{
    packageToResponse(pkg);
}
