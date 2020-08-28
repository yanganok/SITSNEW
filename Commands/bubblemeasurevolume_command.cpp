#include "bubblemeasurevolume_command.h"

BubbleMeasureVolume_Command::BubbleMeasureVolume_Command()
{

}

BubbleMeasureVolume_Command::BubbleMeasureVolume_Command(InstrumentOperator *operate,  Response *response, int msec, quint8 sensorId)
    :Command(operate, response, msec), _sensorId(sensorId)
{

}

bool BubbleMeasureVolume_Command::package(QByteArray &arr)
{
    return true;
}

bool BubbleMeasureVolume_Command::packageToResponse(QByteArray &arr)
{
    return true;
}
