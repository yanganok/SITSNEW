#include "sampleheaterdisable_command.h"

SampleHeaterDisable_Command::SampleHeaterDisable_Command()
{

}

SampleHeaterDisable_Command::SampleHeaterDisable_Command(InstrumentOperator *operate,  Response *response, int msec)
    :Command(operate, response, msec)
{

}

bool SampleHeaterDisable_Command::package(QByteArray &arr)
{
    return true;
}

bool SampleHeaterDisable_Command::packageToResponse(QByteArray &arr)
{
    return true;
}
