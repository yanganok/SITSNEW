#ifndef FLOWCELLDOORGETSEADISTANCE_COMMAND_H
#define FLOWCELLDOORGETSEADISTANCE_COMMAND_H
#include "command.h"

class FlowcellDoorGetSealDistance_Command:public Command
{
    Q_OBJECT
public:
    FlowcellDoorGetSealDistance_Command();
    FlowcellDoorGetSealDistance_Command(InstrumentOperator* operate,  Response *response, int msec);
protected:
    bool package(QByteArray& arr) override;
    bool packageToResponse(QByteArray& arr) override;
};

#endif // FLOWCELLDOORGETSEADISTANCE_COMMAND_H
