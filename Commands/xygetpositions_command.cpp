#include "xygetpositions_command.h"
#include "Responses/xygetposition_command_response.h"

XYGetPositions_Command::XYGetPositions_Command()
{

}

void XYGetPositions_Command::receiveResponse(QByteArray pkg)
{
    packageToResponse(pkg);
}

XYGetPositions_Command::XYGetPositions_Command(InstrumentOperator *operate,  Response *response, int msec, CommunicateCoreUnderlying::XYStageDeviceId deviceId, int xPos, int yPos)
    :Command(operate, response, msec),  _deviceId(deviceId)
{
    _typeName = classtype();
    _xPos = xPos;
    _yPos = yPos;
    DebugOut(QString("组包,命令Id:%1").arg(Command::id()));
    DebugOut(_typeName);
}
bool XYGetPositions_Command::package(QByteArray &arr)
{
    arr = Command::toPackage(static_cast<quint8>(CommunicateCoreUnderlying::CommandType::SEND)
                       , static_cast<quint8>(CommunicateCoreUnderlying::DevicType::DE_TP_fcLEVEL_xyPLATFORM)
                       , static_cast<quint8>(_deviceId)
                       , static_cast<quint8>(CommunicateCoreUnderlying::XYStageControlWord::CW_xySTAGE_CURRENT_LOCATION_GET)
                       , QVector<qint32>{static_cast<qint32>(_xPos), static_cast<qint32>(_yPos)});
    Command::package(arr);
    return true;
}

bool XYGetPositions_Command::packageToResponse(QByteArray &arr)
{
    CommunicateCoreUnderlying::XYStageDeviceId deviceId;
    if(*(arr.data() + 9) == (quint8)CommunicateCoreUnderlying::XYStageControlWord::CW_xySTAGE_CURRENT_LOCATION_GET)
    {
        int code;
        code = BytesToAny::toInt((quint8 *)arr.data() + 3);
        int xPos = BytesToAny::toInt((quint8 *)(arr.data() + 11));
        int yPos = BytesToAny::toInt((quint8 *)(arr.data() + 15));
        CommunicateCoreUnderlying::XYStageStatusWord status = static_cast<CommunicateCoreUnderlying::XYStageStatusWord>(BytesToAny::toQUint16((quint8 *)(arr.data() + 19)));
        deviceId = static_cast<CommunicateCoreUnderlying::XYStageDeviceId>(*(arr.data() + 8));
        std::shared_ptr<XYGetPosition_Command_Response> response(new XYGetPosition_Command_Response(code, deviceId, xPos, yPos, status));
        emit translateResponseToOperator(response);
        Command::packageToResponse(arr);
    }
    return true;
}
