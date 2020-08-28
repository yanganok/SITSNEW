#include "sampleheatercalculatepoints_command_response.h"

SampleHeaterCalculatePoints_Command_Response::SampleHeaterCalculatePoints_Command_Response()
{
    _typeName = classtype();
}

SampleHeaterCalculatePoints_Command_Response::SampleHeaterCalculatePoints_Command_Response(int RFIDMilliDegrees, int FCMilliDegrees)
    :_rfidMilliDegrees(RFIDMilliDegrees), _fcMilliDegrees(FCMilliDegrees)
{
    _typeName = classtype();
}
