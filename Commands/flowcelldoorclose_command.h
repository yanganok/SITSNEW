#ifndef FLOWCELLDOORCLOSE_COMMAND_H
#define FLOWCELLDOORCLOSE_COMMAND_H
#include "command.h"

class FlowcellDoorClose_Command : public Command
{
    Q_OBJECT
public:
    FlowcellDoorClose_Command();
    FlowcellDoorClose_Command(InstrumentOperator* operate,  Response *response, int msec);
protected:
    bool package(QByteArray& arr) override;
    bool packageToResponse(QByteArray& arr) override;
};

#endif // FLOWCELLDOORCLOSE_COMMAND_H
