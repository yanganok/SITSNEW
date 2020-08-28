#include "sampleheatercalculatereset_command.h"

SampleHeaterCalculateReset_Command::SampleHeaterCalculateReset_Command()
{

}

SampleHeaterCalculateReset_Command::SampleHeaterCalculateReset_Command(InstrumentOperator *operate,  Response *response, int msec)
    :Command(operate, response, msec)
{

}

bool SampleHeaterCalculateReset_Command::package(QByteArray &arr)
{
    return true;
}

bool SampleHeaterCalculateReset_Command::packageToResponse(QByteArray &arr)
{
    return true;
}
