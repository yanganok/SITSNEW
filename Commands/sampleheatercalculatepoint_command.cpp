#include "sampleheatercalculatepoint_command.h"

SampleHeaterCalculatePoint_Command::SampleHeaterCalculatePoint_Command()
{

}

SampleHeaterCalculatePoint_Command::SampleHeaterCalculatePoint_Command(InstrumentOperator *operate,  Response *response, int msec, int RFIDMilliDegrees, int FCMilliDegrees)
    :Command(operate, response, msec), _rfidMilliDegrees(RFIDMilliDegrees), _fcMilliDegrees(FCMilliDegrees)
{

}

bool SampleHeaterCalculatePoint_Command::package(QByteArray &arr)
{
    return true;
}

bool SampleHeaterCalculatePoint_Command::packageToResponse(QByteArray &arr)
{
    return true;
}
