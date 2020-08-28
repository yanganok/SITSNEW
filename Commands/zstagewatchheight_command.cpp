#include "zstagewatchheight_command.h"

ZStageWatchHeight_Command::ZStageWatchHeight_Command()
{

}

ZStageWatchHeight_Command::ZStageWatchHeight_Command(InstrumentOperator *operate,  Response *response, int msec, quint32 sensors)
    :Command(operate, response, msec), _sensors(sensors)
{

}

bool ZStageWatchHeight_Command::package(QByteArray &arr)
{
    return true;
}

bool ZStageWatchHeight_Command::packageToResponse(QByteArray &arr)
{
    return true;
}
