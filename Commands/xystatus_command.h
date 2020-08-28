#ifndef XYSTATUS_COMMAND_H
#define XYSTATUS_COMMAND_H
#include "command.h"

class XYStatus_Command : public Command
{
    Q_OBJECT
public:
    XYStatus_Command();
    XYStatus_Command(InstrumentOperator* operate,  Response *response, int msec);
protected:
    bool package(QByteArray& arr) override;
    bool packageToResponse(QByteArray& arr) override;
};

#endif // XYSTATUS_COMMAND_H
