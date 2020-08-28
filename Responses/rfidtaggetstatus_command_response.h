#ifndef RFIDTAGGETSTATUS_COMMAND_RESPONSE_H
#define RFIDTAGGETSTATUS_COMMAND_RESPONSE_H
#include "response.h"
#include "globals/enums.h"

using namespace RFID_Module;
class RFIDTagGetStatus_Command_Response : public Response
{
public:
    RFIDTagGetStatus_Command_Response();
    RFIDTagGetStatus_Command_Response(RFIDTagStatus status);
public:
    inline RFIDTagStatus status()const{return _status;}
private:
    RFIDTagStatus _status;
};
Q_DECLARE_METATYPE(RFIDTagGetStatus_Command_Response)
#endif // RFIDTAGGETSTATUS_COMMAND_RESPONSE_H
