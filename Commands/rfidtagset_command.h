#ifndef RFIDTAGSET_COMMAND_H
#define RFIDTAGSET_COMMAND_H
#include "command.h"
#include "Responses/rfidtag_command_response.h"
#include "globals/enums.h"

using namespace RFID_Module;
class RFIDTagSet_Command : public Command
{
    Q_OBJECT
public:
    RFIDTagSet_Command();
    RFIDTagSet_Command(InstrumentOperator* operate,  Response *response, int msec, RFIDTagId tagId, RFIDTag_Command_Response tag);
public:
    inline RFIDTagId tagId()const{return _tagId;}
    inline const RFIDTag_Command_Response& tag()const{return _tag;}
protected:
    bool package(QByteArray& arr) override;
    bool packageToResponse(QByteArray& arr) override;
private:
    RFIDTagId _tagId;
    RFIDTag_Command_Response _tag;
};

#endif // RFIDTAGSET_COMMAND_H
