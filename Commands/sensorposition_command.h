#ifndef SENSORPOSITION_COMMAND_H
#define SENSORPOSITION_COMMAND_H
#include "command.h"

class SensorPosition_Command : public Command
{
    Q_OBJECT
public:
    SensorPosition_Command();
    SensorPosition_Command(InstrumentOperator* operate,  Response *response, int msec);
protected:
    bool package(QByteArray& arr) override;
    bool packageToResponse(QByteArray& arr) override;
};

#endif // SENSORPOSITION_COMMAND_H
