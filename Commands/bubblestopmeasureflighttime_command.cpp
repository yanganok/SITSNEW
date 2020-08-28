#include "bubblestopmeasureflighttime_command.h"

BubbleStopMeasureFlightTime_Command::BubbleStopMeasureFlightTime_Command()
{

}

BubbleStopMeasureFlightTime_Command::BubbleStopMeasureFlightTime_Command(InstrumentOperator *operate,  Response *response, int msec, CommunicateCoreUnderlying::BubbleDeviceId deviceId)
    :Command(operate, response, msec), _deviceId(deviceId)
{
    _typeName = classtype();
    DebugOut(QString("组包,命令Id:%1").arg(Command::id()));
    DebugOut(_typeName);
}

bool BubbleStopMeasureFlightTime_Command::package(QByteArray &arr)
{
    arr = Command::toPackage(static_cast<quint8>(CommunicateCoreUnderlying::CommandType::SEND)
                       , static_cast<quint8>(CommunicateCoreUnderlying::DevicType::DE_TP_BUBBLE)
                       , static_cast<quint8>(_deviceId)
                       , static_cast<quint8>(CommunicateCoreUnderlying::MeasureFlightTimeBubbleControlWord::CW_BUBBLE_ENDMEASURE_TIME)
                       ,QVector<quint32>());
    Command::package(arr);
    return true;
}

bool BubbleStopMeasureFlightTime_Command::packageToResponse(QByteArray &arr)
{
    return true;
}
