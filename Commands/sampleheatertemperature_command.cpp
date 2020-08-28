#include "sampleheatertemperature_command.h"

SampleHeaterTemperature_Command::SampleHeaterTemperature_Command()
{

}

SampleHeaterTemperature_Command::SampleHeaterTemperature_Command(InstrumentOperator *operate,  Response *response, int msec, bool flowcell_RTD)
    :Command(operate, response, msec), _flowcell_RTD(flowcell_RTD)
{

}

bool SampleHeaterTemperature_Command::package(QByteArray &arr)
{
    return true;
}

bool SampleHeaterTemperature_Command::packageToResponse(QByteArray &arr)
{
    return true;
}
