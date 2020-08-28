#ifndef RFIDTAGGETSTATUS_COMMAND_H
#define RFIDTAGGETSTATUS_COMMAND_H
#include "command.h"
#include "globals/enums.h"

using namespace RFID_Module;
class RFIDTagGetStatus_Command : public Command
{
    Q_OBJECT
public:
    RFIDTagGetStatus_Command();
    RFIDTagGetStatus_Command(RFIDTagId tagId);
public:
    inline RFIDTagId tagId()const{return _tagId;}
protected:
    bool package(QByteArray& arr) override;
    bool packageToResponse(QByteArray& arr) override;
private:
    RFIDTagId _tagId;
};

#endif // RFIDTAGGETSTATUS_COMMAND_H
