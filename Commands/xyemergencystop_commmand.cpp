#include "xyemergencystop_commmand.h"
#include "Responses/xyemergencystop_commmand_response.h"

XYEmergencyStop_Commmand::XYEmergencyStop_Commmand()
{

}

XYEmergencyStop_Commmand::XYEmergencyStop_Commmand(InstrumentOperator *operate, Response *response, int msec, CommunicateCoreUnderlying::XYStageDeviceId deviceId)
    :Command(operate, response, msec), _deviceId(deviceId)
{
    _typeName = classtype();
    DebugOut(QString("组包,命令Id:%1").arg(Command::id()));
    DebugOut(_typeName);
}

void XYEmergencyStop_Commmand::receiveResponse(QByteArray pkg)
{
    packageToResponse(pkg);
}

bool XYEmergencyStop_Commmand::package(QByteArray &arr)
{
    arr = Command::toPackage(static_cast<quint8>(CommunicateCoreUnderlying::CommandType::SEND)
                       , static_cast<quint8>(CommunicateCoreUnderlying::DevicType::DE_TP_fcLEVEL_xyPLATFORM)
                       , static_cast<quint8>(_deviceId)
                       , static_cast<quint8>(CommunicateCoreUnderlying::XYStageControlWord::CW_xySTAGE_STOP)
                       ,QVector<quint32>());
    Command::package(arr);
    return true;
}

bool XYEmergencyStop_Commmand::packageToResponse(QByteArray &arr)
{
    CommunicateCoreUnderlying::XYStageDeviceId deviceId;
    if(*(arr.data() + 9) == (quint8)CommunicateCoreUnderlying::XYStageControlWord::CW_xySTAGE_STOP)
    {
        int code;
        code = BytesToAny::toInt((quint8 *)arr.data() + 3);
        CommunicateCoreUnderlying::XYStageStatusWord status = static_cast<CommunicateCoreUnderlying::XYStageStatusWord>(BytesToAny::toQUint16((quint8 *)(arr.data() + 11)));
        deviceId = static_cast<CommunicateCoreUnderlying::XYStageDeviceId>(*(arr.data() + 8));
        std::shared_ptr<XYEmergencyStop_Commmand_Response> response(new XYEmergencyStop_Commmand_Response(code, deviceId, status));
        emit translateResponseToOperator(response);
        Command::packageToResponse(arr);
    }
    return true;
}
