#ifndef SAMPLEHEATERDISABLE_COMMAND_H
#define SAMPLEHEATERDISABLE_COMMAND_H
#include "command.h"

class SampleHeaterDisable_Command: public Command
{
    Q_OBJECT
public:
    SampleHeaterDisable_Command();
    SampleHeaterDisable_Command(InstrumentOperator* operate,  Response *response, int msec);
protected:
    bool package(QByteArray& arr) override;
    bool packageToResponse(QByteArray& arr) override;
};

#endif // SAMPLEHEATERDISABLE_COMMAND_H
