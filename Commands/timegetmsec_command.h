#ifndef TIMEGETMSEC_COMMAND_H
#define TIMEGETMSEC_COMMAND_H
#include "command.h"

class TimeGetMSEC_Command : public Command
{
    Q_OBJECT
public:
    TimeGetMSEC_Command();
    TimeGetMSEC_Command(InstrumentOperator* operate,  Response *response, int msec);
protected:
    bool package(QByteArray& arr) override;
    bool packageToResponse(QByteArray& arr) override;
};

#endif // TIMEGETMSEC_COMMAND_H
