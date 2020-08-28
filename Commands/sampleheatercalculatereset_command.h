#ifndef SAMPLEHEATERCALCULATERESET_COMMAND_H
#define SAMPLEHEATERCALCULATERESET_COMMAND_H
#include "command.h"

class SampleHeaterCalculateReset_Command : public Command
{
    Q_OBJECT
public:
    SampleHeaterCalculateReset_Command();
    SampleHeaterCalculateReset_Command(InstrumentOperator* operate,  Response *response, int msec);
protected:
    bool package(QByteArray& arr) override;
    bool packageToResponse(QByteArray& arr) override;
};

#endif // SAMPLEHEATERCALCULATERESET_COMMAND_H
