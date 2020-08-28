#include "bubblegetcount_command.h"

BubbleGetCount_Command::BubbleGetCount_Command()
{

}

BubbleGetCount_Command::BubbleGetCount_Command(InstrumentOperator *operate,  Response *response, int msec, quint8 sensor):Command(operate, response, msec)
{
    DebugOut(QString("BubbleGetCount_Command"));
    package(_package);
    Command(operate, response, msec);
}

bool BubbleGetCount_Command::package(QByteArray &arr)
{
    DebugOut(QString("BubbleGetCount_Command:%1").arg("气泡传感器气泡个数包未定"));
    Command::package(arr);
    return true;
}

bool BubbleGetCount_Command::packageToResponse(QByteArray &arr)
{
    return true;
}
