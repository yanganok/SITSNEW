#include "xyfindzero_command.h"
#include "Responses/xyfindzero_command_response.h"

XYFindZero_Command::XYFindZero_Command()
{

}

XYFindZero_Command::XYFindZero_Command(InstrumentOperator *operate, Response *response, int msec, CommunicateCoreUnderlying::XYStageDeviceId deviceId, bool isXFindZero, bool isYFindZero)
    :Command(operate, response, msec), _deviceId(deviceId), _isXFindZero(isXFindZero), _isYFindZero(isYFindZero)
{
    _typeName = classtype();
    DebugOut(QString("组包,命令Id:%1").arg(Command::id()));
    DebugOut(_typeName);
}

void XYFindZero_Command::receiveResponse(QByteArray pkg)
{
    packageToResponse(pkg);
}

bool XYFindZero_Command::package(QByteArray &arr)
{
    if(_isXFindZero && _isYFindZero)
    {
        arr = Command::toPackage(static_cast<quint8>(CommunicateCoreUnderlying::CommandType::SEND)
                           , static_cast<quint8>(CommunicateCoreUnderlying::DevicType::DE_TP_fcLEVEL_xyPLATFORM)
                           , static_cast<quint8>(_deviceId)
                           , static_cast<quint8>(CommunicateCoreUnderlying::XYStageControlWord::CW_xySTAGE_FINDING_XY_ZEROS)
                           ,QVector<quint32>());
    }
    else if(_isXFindZero)
    {
        arr = Command::toPackage(static_cast<quint8>(CommunicateCoreUnderlying::CommandType::SEND)
                           , static_cast<quint8>(CommunicateCoreUnderlying::DevicType::DE_TP_fcLEVEL_xyPLATFORM)
                           , static_cast<quint8>(_deviceId)
                           , static_cast<quint8>(CommunicateCoreUnderlying::XYStageControlWord::CW_xySTAGE_FINDING_X_HOME)
                           ,QVector<quint32>());
    }
    else if(_isYFindZero)
    {
        arr = Command::toPackage(static_cast<quint8>(CommunicateCoreUnderlying::CommandType::SEND)
                           , static_cast<quint8>(CommunicateCoreUnderlying::DevicType::DE_TP_fcLEVEL_xyPLATFORM)
                           , static_cast<quint8>(_deviceId)
                           , static_cast<quint8>(CommunicateCoreUnderlying::XYStageControlWord::CW_xySTAGE_FINDING_Y_HOME)
                           ,QVector<quint32>());
    }
    Command::package(arr);
    return true;
}

bool XYFindZero_Command::packageToResponse(QByteArray &arr)
{
    CommunicateCoreUnderlying::XYStageDeviceId deviceId;
    if(*(arr.data() + 9) == (quint8)CommunicateCoreUnderlying::XYStageControlWord::CW_xySTAGE_FINDING_XY_ZEROS)
    {
        int code;
        code = BytesToAny::toInt((quint8 *)arr.data() + 3);
        CommunicateCoreUnderlying::XYStageStatusWord status = static_cast<CommunicateCoreUnderlying::XYStageStatusWord>(BytesToAny::toQUint16((quint8 *)(arr.data() + 11)));
        deviceId = static_cast<CommunicateCoreUnderlying::XYStageDeviceId>(*(arr.data() + 8));
        std::shared_ptr<XYFindZero_Command_Response> response(new XYFindZero_Command_Response(code, deviceId, status, true, true));
        emit translateResponseToOperator(response);
        Command::packageToResponse(arr);
    }
    else if(*(arr.data() + 9) == (quint8)CommunicateCoreUnderlying::XYStageControlWord::CW_xySTAGE_FINDING_X_HOME)
    {
        int code;
        code = BytesToAny::toInt((quint8 *)arr.data() + 3);
        CommunicateCoreUnderlying::XYStageStatusWord status = static_cast<CommunicateCoreUnderlying::XYStageStatusWord>(BytesToAny::toQUint16((quint8 *)(arr.data() + 11)));
        deviceId = static_cast<CommunicateCoreUnderlying::XYStageDeviceId>(*(arr.data() + 8));
        std::shared_ptr<XYFindZero_Command_Response> response(new XYFindZero_Command_Response(code, deviceId, status, true, false));
        emit translateResponseToOperator(response);
        Command::packageToResponse(arr);
    }
    else if(*(arr.data() + 9) == (quint8)CommunicateCoreUnderlying::XYStageControlWord::CW_xySTAGE_FINDING_Y_HOME)
    {
        int code;
        code = BytesToAny::toInt((quint8 *)arr.data() + 3);
        CommunicateCoreUnderlying::XYStageStatusWord status = static_cast<CommunicateCoreUnderlying::XYStageStatusWord>(BytesToAny::toQUint16((quint8 *)(arr.data() + 11)));
        deviceId = static_cast<CommunicateCoreUnderlying::XYStageDeviceId>(*(arr.data() + 8));
        std::shared_ptr<XYFindZero_Command_Response> response(new XYFindZero_Command_Response(code, deviceId, status, false, true));
        emit translateResponseToOperator(response);
        Command::packageToResponse(arr);
    }
    return true;
}
