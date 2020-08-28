#include "sampleheatertargetget_command_response.h"

SampleHeaterTargetGet_Command_Response::SampleHeaterTargetGet_Command_Response()
{
    _typeName = classtype();
}

SampleHeaterTargetGet_Command_Response::SampleHeaterTargetGet_Command_Response(int milli_degrees_C)
    :_milliDegreesC(milli_degrees_C)
{
    _typeName = classtype();
}
