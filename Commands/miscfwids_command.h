#ifndef MISCFWIDS_COMMAND_H
#define MISCFWIDS_COMMAND_H
#include "command.h"

class MiscFWIds_Command : public Command
{
    Q_OBJECT
public:
    MiscFWIds_Command();
    MiscFWIds_Command(InstrumentOperator* operate,  Response *response, int msec);
protected:
    bool package(QByteArray& arr) override;
    bool packageToResponse(QByteArray& arr) override;
};

#endif // MISCFWIDS_COMMAND_H
