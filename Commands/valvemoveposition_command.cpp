#include "valvemoveposition_command.h"
#include "Responses/valvemoveposition_command_response.h"

ValveMovePosition_Command::ValveMovePosition_Command()
{
    _typeName = classtype();
}

ValveMovePosition_Command::ValveMovePosition_Command(InstrumentOperator *operate, Response *response, int msec, CommunicateCoreUnderlying::ValveDeviceId deviceId, qint16 pos, QString key, bool async, int delayMs)
    :Command(operate, response, msec, key, async, delayMs), _deviceId(deviceId), _pos(pos)
{
    _typeName = classtype();
}

bool ValveMovePosition_Command::package(QByteArray &arr)
{
    arr = Command::toPackage(static_cast<quint8>(CommunicateCoreUnderlying::CommandType::SEND),
                static_cast<quint8>(CommunicateCoreUnderlying::DevicType::DE_TP_DISTRIBUTION_VALVE),
                static_cast<quint8>(_deviceId),
                static_cast<quint8>(CommunicateCoreUnderlying::ValveControlWord::CW_VALVE_GO),
                QVector<quint16>{static_cast<quint16>(_pos)}
                );
    Command::package(arr);
    return true;
}

bool ValveMovePosition_Command::packageToResponse(QByteArray &arr)
{
    int code;
    code = BytesToAny::toInt((quint8 *)arr.data() + 3);
    if(*(arr.data() + 9) == (quint8)CommunicateCoreUnderlying::ValveControlWord::CW_VALVE_INIT)
    {

        CommunicateCoreUnderlying::ValveDeviceId deviceId = static_cast<CommunicateCoreUnderlying::ValveDeviceId>(*((quint8 *)arr.data() + 8));
        int curpos = BytesToAny::toQInt16((quint8 *)arr.data() + 11);
        std::shared_ptr<ValveMovePosition_Command_Response> response(new ValveMovePosition_Command_Response(code, deviceId, curpos, _key));
        emit translateResponseToOperator(response);
        Command::packageToResponse(arr);
    }
    return true;
}

void ValveMovePosition_Command::receiveResponse(QByteArray pkg)
{
    packageToResponse(pkg);
}
