#ifndef SAMPLEHEATERTARGETGET_COMMAND_H
#define SAMPLEHEATERTARGETGET_COMMAND_H
#include "command.h"

class SampleHeaterTargetGet_Command : public Command
{
    Q_OBJECT
public:
    SampleHeaterTargetGet_Command();
    SampleHeaterTargetGet_Command(InstrumentOperator* operate,  Response *response, int msec);
protected:
    bool package(QByteArray& arr) override;
    bool packageToResponse(QByteArray& arr) override;
};

#endif // SAMPLEHEATERTARGETGET_COMMAND_H
