#include "rfidtagget_command_response.h"

RFIDTagGet_Command_Response::RFIDTagGet_Command_Response()
{
    _typeName = classtype();
}

RFIDTagGet_Command_Response::RFIDTagGet_Command_Response(RFIDTag_Command_Response tag)
    :_tag(tag)
{
    _typeName = classtype();
}
