#include "valvegetposition_command.h"
#include "Responses/valvegetposition_command_response.h"

ValveGetPosition_Command::ValveGetPosition_Command()
{
    _typeName = classtype();
}


bool ValveGetPosition_Command::package(QByteArray &arr)
{
    arr = Command::toPackage(static_cast<quint8>(CommunicateCoreUnderlying::CommandType::SEND),
                static_cast<quint8>(CommunicateCoreUnderlying::DevicType::DE_TP_DISTRIBUTION_VALVE),
                static_cast<quint8>(_deviceId),
                static_cast<quint8>(CommunicateCoreUnderlying::ValveControlWord::CW_VALVE_INIT),
                QVector<quint16>()
                );
    Command::package(arr);
    return true;
}

bool ValveGetPosition_Command::packageToResponse(QByteArray &arr)
{
    int code;
    code = BytesToAny::toInt((quint8 *)arr.data() + 3);
    if(*(arr.data() + 9) == (quint8)CommunicateCoreUnderlying::ValveControlWord::CW_VALVE_INIT)
    {

        CommunicateCoreUnderlying::ValveDeviceId deviceId = static_cast<CommunicateCoreUnderlying::ValveDeviceId>(*((quint8 *)arr.data() + 8));
        int curpos = BytesToAny::toQInt16((quint8 *)arr.data() + 11);
//        std::shared_ptr<ValveGetPosition_Command_Response> response(new ValveGetPosition_Command_Response(code, deviceId, curpos));
//        emit translateResponseToOperator(response);
        Command::packageToResponse(arr);
    }
    return true;
}

void ValveGetPosition_Command::receiveResponse(QByteArray pkg)
{
    packageToResponse(pkg);
}

ValveGetPosition_Command::ValveGetPosition_Command(InstrumentOperator* operate,  Response *response, int msec, CommunicateCoreUnderlying::ValveDeviceId deviceId, QString key, bool async, int delayMs)
    :Command(operate, response, msec, key, async, delayMs), _deviceId(deviceId)
{

}
