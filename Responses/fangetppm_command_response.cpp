#include "fangetppm_command_response.h"

FanGetPPM_Command_Response::FanGetPPM_Command_Response()
{
    _typeName = classtype();
}

FanGetPPM_Command_Response::FanGetPPM_Command_Response(quint32 ppm):_ppm(ppm)
{
    _typeName = classtype();
}
