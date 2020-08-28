#ifndef RFIDTAGRESET_COMMAND_H
#define RFIDTAGRESET_COMMAND_H
#include"command.h"

using namespace RFID_Module;
class RFIDTagReset_Command : public Command
{
    Q_OBJECT
public:
    RFIDTagReset_Command();
    RFIDTagReset_Command(InstrumentOperator* operate,  Response *response, int msec, RFIDTagId rfid);
public:
    inline RFIDTagId rfid()const{return _rfid;}
protected:
    bool package(QByteArray& arr) override;
    bool packageToResponse(QByteArray& arr) override;
private:
    RFIDTagId _rfid;
};

#endif // RFIDTAGRESET_COMMAND_H
