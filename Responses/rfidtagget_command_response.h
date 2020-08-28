#ifndef RFIDTAGGET_COMMAND_RESPONSE_H
#define RFIDTAGGET_COMMAND_RESPONSE_H
#include "response.h"
#include "rfidtag_command_response.h"

class RFIDTagGet_Command_Response : public Response
{
public:
    RFIDTagGet_Command_Response();
    RFIDTagGet_Command_Response(RFIDTag_Command_Response tag);
public:
    inline const RFIDTag_Command_Response& tag()const{return _tag;}
private:
    RFIDTag_Command_Response _tag;
};
Q_DECLARE_METATYPE(RFIDTagGet_Command_Response)
#endif // RFIDTAGGET_COMMAND_RESPONSE_H
