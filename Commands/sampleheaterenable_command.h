#ifndef SAMPLEHEATERENABLE_COMMAND_H
#define SAMPLEHEATERENABLE_COMMAND_H
#include "command.h"

class SampleHeaterEnable_Command:Command
{
    Q_OBJECT
public:
    SampleHeaterEnable_Command();
    SampleHeaterEnable_Command(InstrumentOperator* operate,  Response *response, int msec);
protected:
    bool package(QByteArray& arr) override;
    bool packageToResponse(QByteArray& arr) override;
};

#endif // SAMPLEHEATERENABLE_COMMAND_H
