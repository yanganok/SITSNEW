#include "xymovetohomepoint_command.h"
#include "Responses/xymovetohomepoint_command_response.h"

XYMoveToHomePoint_Command::XYMoveToHomePoint_Command()
{
    _typeName = classtype();
}

XYMoveToHomePoint_Command::XYMoveToHomePoint_Command(InstrumentOperator *operate, Response *response, int msec, CommunicateCoreUnderlying::XYStageDeviceId deviceId, QString key, bool async, int delayMs)
    :Command(operate, response,msec, key, async, delayMs), _deviceId(deviceId)
{
    _typeName = classtype();
    DebugOut(QString("组包,命令Id:%1").arg(Command::id()));
    DebugOut(_typeName);
}

void XYMoveToHomePoint_Command::receiveResponse(QByteArray pkg)
{
    packageToResponse(pkg);
}

bool XYMoveToHomePoint_Command::package(QByteArray &arr)
{
    arr = Command::toPackage(static_cast<quint8>(CommunicateCoreUnderlying::CommandType::SEND)
                       , static_cast<quint8>(CommunicateCoreUnderlying::DevicType::DE_TP_fcLEVEL_xyPLATFORM)
                       , static_cast<quint8>(_deviceId)
                       , static_cast<quint8>(CommunicateCoreUnderlying::XYStageControlWord::CW_xySTAGE_FOLLOW_TO_HOME_P)
                       ,QVector<quint32>());
    Command::package(arr);
    return true;
}

bool XYMoveToHomePoint_Command::packageToResponse(QByteArray &arr)
{
    CommunicateCoreUnderlying::XYStageDeviceId deviceId;
    if(*(arr.data() + 9) == (quint8)CommunicateCoreUnderlying::XYStageControlWord::CW_xySTAGE_INIT)
    {
        int code;
        code = BytesToAny::toInt((quint8 *)arr.data() + 3);
        CommunicateCoreUnderlying::XYStageStatusWord status = static_cast<CommunicateCoreUnderlying::XYStageStatusWord>(BytesToAny::toQUint16((quint8 *)(arr.data() + 11)));
        deviceId = static_cast<CommunicateCoreUnderlying::XYStageDeviceId>(*(arr.data() + 8));
        std::shared_ptr<XYMoveToHomePoint_Command_Response> response(new XYMoveToHomePoint_Command_Response(code, deviceId, status));
        emit translateResponseToOperator(response);
        Command::packageToResponse(arr);
    }
    return true;
}
