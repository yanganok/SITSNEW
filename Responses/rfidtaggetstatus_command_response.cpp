#include "rfidtaggetstatus_command_response.h"

RFIDTagGetStatus_Command_Response::RFIDTagGetStatus_Command_Response()
{
    _typeName = classtype();
}

RFIDTagGetStatus_Command_Response::RFIDTagGetStatus_Command_Response(RFIDTagStatus status)
    :_status(status)
{
    _typeName = classtype();
}
