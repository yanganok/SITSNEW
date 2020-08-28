#include "bubblecalibrate_command.h"

BubbleCalibrate_Command::BubbleCalibrate_Command()
{

}

BubbleCalibrate_Command::BubbleCalibrate_Command(InstrumentOperator* operate,  Response *response, int msec)
{
    DebugOut(QString("BubbleCalibrate_Command"));
    package(_package);
    Command(operate, response, msec);
}

bool BubbleCalibrate_Command::package(QByteArray &arr)
{
//    QVector<quint32> paras{0x05};
//    arr = std::move(this->toPackage(0x01, 0x02, 0x03, 0x04, paras));
    DebugOut(QString("BubbleCalibrate_Command:%1").arg("气泡传感器校准包未定"));
    Command::package(arr);
    return true;
}

bool BubbleCalibrate_Command::packageToResponse(QByteArray& arr)
{
    return true;
}
