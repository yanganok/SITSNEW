#ifndef RFIDTAGVALIDATION_COMMAND_H
#define RFIDTAGVALIDATION_COMMAND_H
#include "command.h"

class RFIDTagValidation_Command : public Command
{
    Q_OBJECT
public:
    RFIDTagValidation_Command();
    RFIDTagValidation_Command(InstrumentOperator* operate,  Response *response, int msec, bool enable_nDisable);
public:
    bool enable_nDisable()const{return _enable_nDisable;}
protected:
    bool package(QByteArray& arr) override;
    bool packageToResponse(QByteArray& arr) override;
private:
    bool _enable_nDisable;
};

#endif // RFIDTAGVALIDATION_COMMAND_H
