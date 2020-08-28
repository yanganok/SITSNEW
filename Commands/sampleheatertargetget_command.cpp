#include "sampleheatertargetget_command.h"

SampleHeaterTargetGet_Command::SampleHeaterTargetGet_Command()
{

}

SampleHeaterTargetGet_Command::SampleHeaterTargetGet_Command(InstrumentOperator *operate,  Response *response, int msec)
    :Command(operate, response, msec)
{

}

bool SampleHeaterTargetGet_Command::package(QByteArray &arr)
{
    return true;
}

bool SampleHeaterTargetGet_Command::packageToResponse(QByteArray &arr)
{
    return true;
}
