#include "xyoffsets_command.h"
#include "Responses/xymoveto_command_response.h"

XYOffsets_Command::XYOffsets_Command()
{

}

XYOffsets_Command::XYOffsets_Command(InstrumentOperator *operate,  Response *response, int msec, CommunicateCoreUnderlying::BubbleDeviceId deviceId, int x_nm, int y_nm, QString key, bool async, int delayMs)
    :Command(operate, response, msec, key, async, delayMs), _x_nm(x_nm), _y_nm(y_nm), _deviceId(deviceId)
{
    _typeName = classtype();
    _x_nm = x_nm;
    _y_nm = y_nm;
    DebugOut(QString("组包,命令Id:%1").arg(Command::id()));
    DebugOut(_typeName);
}

void XYOffsets_Command::receiveResponse(QByteArray pkg)
{
    packageToResponse(pkg);
}

bool XYOffsets_Command::package(QByteArray &arr)
{
    arr = Command::toPackage(static_cast<quint8>(CommunicateCoreUnderlying::CommandType::SEND)
                       , static_cast<quint8>(CommunicateCoreUnderlying::DevicType::DE_TP_fcLEVEL_xyPLATFORM)
                       , static_cast<quint8>(_deviceId)
                       , static_cast<quint8>(CommunicateCoreUnderlying::XYStageControlWord::CW_xySTAGE_P_TO_P_RELATIVE)
                       , QVector<quint32>{static_cast<quint32>(_x_nm), static_cast<quint32>(_y_nm)});
    Command::package(arr);
    return true;
}

bool XYOffsets_Command::packageToResponse(QByteArray &arr)
{
//    CommunicateCoreUnderlying::XYStageDeviceId deviceId;
//    if(*(arr.data() + 9) == (quint8)CommunicateCoreUnderlying::XYStageControlWord::CW_xySTAGE_STOP)
//    {
//        int code;
//        code = BytesToAny::toInt((quint8 *)arr.data() + 3);
//        CommunicateCoreUnderlying::XYStageStatusWord status = static_cast<CommunicateCoreUnderlying::XYStageStatusWord>(BytesToAny::toQUint16((quint8 *)(arr.data() + 11)));
//        deviceId = static_cast<CommunicateCoreUnderlying::XYStageDeviceId>(*(arr.data() + 8));
//        std::shared_ptr<XYMoveTo_Command_Response> response(new XYMoveTo_Command_Response(code, deviceId, status));

//        emit translateResponseToOperator(response);
//        Command::packageToResponse(arr);
//    }
    return true;
}
