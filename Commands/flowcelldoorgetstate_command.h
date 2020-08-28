#ifndef FLOWCELLDOORGETSTATE_COMMAND_H
#define FLOWCELLDOORGETSTATE_COMMAND_H
#include "command.h"

class FlowcellDoorGetState_Command : public Command
{
    Q_OBJECT
public:
    FlowcellDoorGetState_Command();
    FlowcellDoorGetState_Command(InstrumentOperator* operate,  Response *response, int msec);
protected:
    bool package(QByteArray& arr) override;
    bool packageToResponse(QByteArray& arr) override;
};

#endif // FLOWCELLDOORGETSTATE_COMMAND_H
