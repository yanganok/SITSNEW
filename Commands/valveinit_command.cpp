#include "valveinit_command.h"
#include "Responses/valveinit_command_response.h"

ValveInit_Command::ValveInit_Command()
{
    _typeName = classtype();
}

ValveInit_Command::ValveInit_Command(InstrumentOperator *operate, Response *response, int msec, CommunicateCoreUnderlying::ValveDeviceId deviceId, QString key, bool async, int delayMs)
    :Command(operate, response, msec, key, async, delayMs), _deviceId(deviceId)
{
    _typeName = classtype();
}

bool ValveInit_Command::package(QByteArray &arr)
{
    arr = Command::toPackage(static_cast<quint8>(CommunicateCoreUnderlying::CommandType::SEND),
                static_cast<quint8>(CommunicateCoreUnderlying::DevicType::DE_TP_DISTRIBUTION_VALVE),
                static_cast<quint8>(_deviceId),
                static_cast<quint8>(CommunicateCoreUnderlying::ValveControlWord::CW_VALVE_INIT),
                QVector<quint32>()
                );
    Command::package(arr);
    return true;
}

bool ValveInit_Command::packageToResponse(QByteArray &arr)
{
    int code;
    code = BytesToAny::toInt((quint8 *)arr.data() + 3);
    if(*(arr.data() + 9) == (quint8)CommunicateCoreUnderlying::ValveControlWord::CW_VALVE_INIT)
    {

        CommunicateCoreUnderlying::ValveDeviceId deviceId = static_cast<CommunicateCoreUnderlying::ValveDeviceId>(*((quint8 *)arr.data() + 8));
        int stausCode = BytesToAny::toQInt16((quint8 *)arr.data() + 11);
        std::shared_ptr<ValveInit_Command_Response> response(new ValveInit_Command_Response(code, deviceId, static_cast<CommunicateCoreUnderlying::ValveStatusWord>(stausCode),  _key));
        emit translateResponseToOperator(response);
        Command::packageToResponse(arr);
    }
    return true;
}

void ValveInit_Command::receiveResponse(QByteArray pkg)
{
    packageToResponse(pkg);
}
