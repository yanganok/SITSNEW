#include "pumpabsorb_command.h"

PumpAbsorb_Command::PumpAbsorb_Command():Pump_Command()
{
    _typeName = classtype();
}

PumpAbsorb_Command::PumpAbsorb_Command(InstrumentOperator *operate, Response *response, int msec, CommunicateCoreUnderlying::SyringPumpId deviceId, quint16 valveId, quint16 pumpSpeed, qint16 volumn, QString key , bool async, int delayMs )
    :Pump_Command(operate, response, msec, key, async, delayMs), _valveId(valveId), _pumpSpeed(pumpSpeed), _volumn(volumn), _deviceId(deviceId)
{
    _typeName = classtype();
}

bool PumpAbsorb_Command::package(QByteArray &arr)
{
    arr = Command::toPackage(static_cast<quint8>(CommunicateCoreUnderlying::CommandType::SEND),
                static_cast<quint8>(CommunicateCoreUnderlying::DevicType::DE_TP_SYRINGE),
                static_cast<quint8>(_deviceId),
                static_cast<quint8>(CommunicateCoreUnderlying::SyringPumpControlWord::CW_SYRINGE_MOVE),
                QVector<quint16>{static_cast<quint16>(_valveId),
                                 static_cast<quint16>(qRound(_pumpSpeed * Fluidics_Module::stepsPerUl * 0.016666666666666666 * 2)),
                                 static_cast<quint16>(_curPos / Fluidics_Module::stepsPerUl  + _volumn > Fluidics_Module::fullScaleVolume ? Fluidics_Module::fullScaleVolume:_curPos / Fluidics_Module::stepsPerUl + _volumn )}
                );
    Command::package(arr);
    return true;
}

bool PumpAbsorb_Command::packageToResponse(QByteArray &arr)
{
    CommunicateCoreUnderlying::SyringPumpId deviceId;
    int code;
    quint16 bubbleCode;
    quint32 bubbleIntervalus;
    code = BytesToAny::toInt((quint8 *)arr.data() + 3);
    if(*(arr.data() + 9) == (quint8)CommunicateCoreUnderlying::SyringPumpControlWord::CW_SYRINGE_MOVE && id() == code)
    {
        deviceId = static_cast<CommunicateCoreUnderlying::SyringPumpId>(*(arr.data() + 8));
        _curPos = BytesToAny::toQInt16((quint8 *)arr.data() + 11);
//        bubbleIntervalus = BytesToAny::toQUint32((quint8 *)arr.data() + 13);
        std::shared_ptr<PumpAbsorb_Command_Response> response(new PumpAbsorb_Command_Response(code, deviceId, _curPos, _key));
//        response->setId(code);
//        //QDateTime::currentDateTime()::toString();
//        QString curDate = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss:zzz");
//        response->setRecDateTime(curDate);
        emit translateResponseToOperator(response);
        Command::packageToResponse(arr);
    }
    return true;
}

void PumpAbsorb_Command::receiveResponse(QByteArray pkg)
{
    packageToResponse(pkg);
}
