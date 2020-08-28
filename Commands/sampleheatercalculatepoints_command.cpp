#include "sampleheatercalculatepoints_command.h"

SampleHeaterCalculatePoints_Command::SampleHeaterCalculatePoints_Command()
{

}

SampleHeaterCalculatePoints_Command::SampleHeaterCalculatePoints_Command(InstrumentOperator *operate,  Response *response, int msec)
    :Command(operate, response, msec)
{

}

bool SampleHeaterCalculatePoints_Command::package(QByteArray &arr)
{
    return true;
}

bool SampleHeaterCalculatePoints_Command::packageToResponse(QByteArray &arr)
{
    return true;
}
