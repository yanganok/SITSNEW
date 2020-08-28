#include "sampleheaterenable_command.h"

SampleHeaterEnable_Command::SampleHeaterEnable_Command()
{

}

SampleHeaterEnable_Command::SampleHeaterEnable_Command(InstrumentOperator *operate,  Response *response, int msec)
    :Command(operate, response, msec)
{

}

bool SampleHeaterEnable_Command::package(QByteArray &arr)
{
    return true;
}

bool SampleHeaterEnable_Command::packageToResponse(QByteArray &arr)
{
    return true;
}
