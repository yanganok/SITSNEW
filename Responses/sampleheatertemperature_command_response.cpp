#include "sampleheatertemperature_command_response.h"

SampleHeaterTemperature_Command_Response::SampleHeaterTemperature_Command_Response()
{
    _typeName = classtype();
}

SampleHeaterTemperature_Command_Response::SampleHeaterTemperature_Command_Response(int milli_degrees_C)
    :_milliDegreesC(milli_degrees_C)
{
    _typeName = classtype();
}
