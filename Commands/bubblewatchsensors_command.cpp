#include "bubblewatchsensors_command.h"

BubbleWatchSensors_Command::BubbleWatchSensors_Command()
{

}

BubbleWatchSensors_Command::BubbleWatchSensors_Command(InstrumentOperator *operate,  Response *response, int msec, int sensor1, int sensor2, int max_period_msec)
    :Command(operate, response, msec),_sensor1(sensor1),_sensor2(sensor2),_max_period_msec(max_period_msec)
{
    DebugOut(QString("BubbleWatchSensors_Command"));
    package(_package);
}

bool BubbleWatchSensors_Command::package(QByteArray &arr)
{
    DebugOut(QString("BubbleWatchSensors_Command:%1").arg("气泡传感器监听包未定"));
    Command::package(arr);
    return true;
}

bool BubbleWatchSensors_Command::packageToResponse(QByteArray &arr)
{
    return true;
}
