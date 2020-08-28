#include "bubblemeasureflighttime_command.h"
#include "Responses/bubblemeasureflighttime_command_response.h"
#include <QDateTime>

BubbleMeasureFlightTime_Command::BubbleMeasureFlightTime_Command()
{
    _typeName = classtype();
}

BubbleMeasureFlightTime_Command::BubbleMeasureFlightTime_Command(InstrumentOperator *operate,  Response *response, int msec, quint8 upstream, quint8 downstream, bool edge, quint32 maxlitch_msec, int timeout_msec, QString key , bool async, int delayMs)
    :Command(operate, response, msec, key, async, delayMs),_upstream(upstream),_downstream(downstream),_edge(edge),_maxglitch_msec(maxlitch_msec), _timeout_msec(timeout_msec)
{
    _typeName = classtype();
    DebugOut(QString("组包,命令Id:%1").arg(Command::id()));
    DebugOut(_typeName);
}

BubbleMeasureFlightTime_Command::BubbleMeasureFlightTime_Command(InstrumentOperator *operate,  Response *response, int msec, CommunicateCoreUnderlying::BubbleDeviceId deviceId, QString key, bool async, int delayMs)
    :Command(operate, response, msec, key, async, delayMs), _deviceId(deviceId)
{
    _typeName = classtype();
    DebugOut(QString("组包,命令Id:%1").arg(Command::id()));
    DebugOut(_typeName);
}

void BubbleMeasureFlightTime_Command::receiveResponse(QByteArray pkg)
{
    packageToResponse(pkg);
}

bool BubbleMeasureFlightTime_Command::package(QByteArray &arr)
{
    arr = Command::toPackage(static_cast<quint8>(CommunicateCoreUnderlying::CommandType::SEND)
                       , static_cast<quint8>(CommunicateCoreUnderlying::DevicType::DE_TP_BUBBLE)
                       , static_cast<quint8>(_deviceId)
                       , static_cast<quint8>(CommunicateCoreUnderlying::MeasureFlightTimeBubbleControlWord::CW_BUBBLE_MEASURE_TIME)
                       ,QVector<quint32>());
    Command::package(arr);
    return true;
}

bool BubbleMeasureFlightTime_Command::packageToResponse(QByteArray &arr)
{
    CommunicateCoreUnderlying::BubbleDeviceId deviceId;
    int code;
    quint16 bubbleCode;
    quint32 bubbleIntervalus;
    code = BytesToAny::toInt((quint8 *)arr.data() + 3);
    if(*(arr.data() + 9) == (quint8)CommunicateCoreUnderlying::MeasureFlightTimeBubbleStautsWord::st_BUBBLE_MEASURERESULT_TIME)
    {
        deviceId = static_cast<CommunicateCoreUnderlying::BubbleDeviceId>(*(arr.data() + 8));
        bubbleCode = BytesToAny::toQUint16((quint8 *)arr.data() + 11);
        bubbleIntervalus = BytesToAny::toQUint32((quint8 *)arr.data() + 13);
        std::shared_ptr<BubbleMeasureFlightTime_Command_Response> response(new BubbleMeasureFlightTime_Command_Response(code, deviceId, bubbleCode, bubbleIntervalus));
//        response->setCmdId(code);
        //QDateTime::currentDateTime()::toString();
        QString curDate = response->recDate().toString("yyyy-MM-dd hh:mm:ss:zzz");
        response->setRecDateTime(curDate);
        emit translateResponseToOperator(response);
        Command::packageToResponse(arr);
    }
    return true;
}
