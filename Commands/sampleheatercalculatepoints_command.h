#ifndef SAMPLEHEATERCALCULATEPOINTS_H
#define SAMPLEHEATERCALCULATEPOINTS_H
#include "command.h"

class SampleHeaterCalculatePoints_Command : public Command
{
    Q_OBJECT
public:
    SampleHeaterCalculatePoints_Command();
    SampleHeaterCalculatePoints_Command(InstrumentOperator* operate,  Response *response, int msec);
protected:
    bool package(QByteArray& arr) override;
    bool packageToResponse(QByteArray& arr) override;
};

#endif // SAMPLEHEATERCALCULATEPOINTS_H
