#include "zstagesetheight_command.h"

ZStageSetHeight_Command::ZStageSetHeight_Command()
{

}

ZStageSetHeight_Command::ZStageSetHeight_Command(InstrumentOperator *operate,  Response *response, int msec, int sensors, QVector<int> &height_nm, quint32 timeout_msec)
    :Command(operate, response, msec), _sensors(sensors), _height_nm(height_nm), _timeout_msec(timeout_msec)
{

}

bool ZStageSetHeight_Command::package(QByteArray &arr)
{
    return true;
}

bool ZStageSetHeight_Command::packageToResponse(QByteArray &arr)
{
    return true;
}
