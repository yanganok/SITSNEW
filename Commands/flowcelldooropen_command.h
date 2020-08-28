#ifndef FLOWCELLDOOROPEN_COMMAND_H
#define FLOWCELLDOOROPEN_COMMAND_H
#include "command.h"

class FlowcellDoorOpen_Command : public Command
{
    Q_OBJECT
public:
    FlowcellDoorOpen_Command();
    FlowcellDoorOpen_Command(InstrumentOperator* operate,  Response *response, int msec);
protected:
    bool package(QByteArray& arr) override;
    bool packageToResponse(QByteArray& arr) override;
};

#endif // FLOWCELLDOOROPEN_COMMAND_H
