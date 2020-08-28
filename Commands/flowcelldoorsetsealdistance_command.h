#ifndef FLOWCELLDOORSETSEALDISTANCE_COMMAND_H
#define FLOWCELLDOORSETSEALDISTANCE_COMMAND_H
#include "command.h"

class FlowcellDoorSetSealDistance_Command : public Command
{
    Q_OBJECT
public:
    FlowcellDoorSetSealDistance_Command();
    FlowcellDoorSetSealDistance_Command(InstrumentOperator* operate,  Response *response, int msec, quint32 steps);
protected:
    bool package(QByteArray& arr) override;
    bool packageToResponse(QByteArray& arr) override;
private:
    quint32 _steps;
};

#endif // FLOWCELLDOORSETSEALDISTANCE_COMMAND_H
