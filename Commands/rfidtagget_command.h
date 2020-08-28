#ifndef RFIDTAGGET_COMMAND_H
#define RFIDTAGGET_COMMAND_H
#include "command.h"

class RFIDTagGet_Command : public Command
{
    Q_OBJECT
public:
    RFIDTagGet_Command();
    RFIDTagGet_Command(InstrumentOperator* operate,  Response *response, int msec, int rfid);
public:
    inline int rfid()const{return _rfid;}
protected:
    bool package(QByteArray& arr) override;
    bool packageToResponse(QByteArray& arr) override;
private:
    int _rfid;
};

#endif // RFIDTAGGET_COMMAND_H
