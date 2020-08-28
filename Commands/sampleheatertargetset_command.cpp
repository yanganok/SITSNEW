#include "sampleheatertargetset_command.h"

SampleHeaterTargetSet_Command::SampleHeaterTargetSet_Command()
{

}

SampleHeaterTargetSet_Command::SampleHeaterTargetSet_Command(InstrumentOperator *operate,  Response *response, int msec, int milli_degrees_C)
    :Command(operate, response, msec), _milliDegreesC(milli_degrees_C)
{

}

bool SampleHeaterTargetSet_Command::package(QByteArray &arr)
{
    return  true;
}

bool SampleHeaterTargetSet_Command::packageToResponse(QByteArray &arr)
{
    return true;
}
