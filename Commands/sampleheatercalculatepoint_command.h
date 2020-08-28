#ifndef SAMPLEHEATERCALCULATEPOINT_COMMAND_H
#define SAMPLEHEATERCALCULATEPOINT_COMMAND_H
#include "command.h"

class SampleHeaterCalculatePoint_Command : public Command
{
    Q_OBJECT
public:
    SampleHeaterCalculatePoint_Command();
    SampleHeaterCalculatePoint_Command(InstrumentOperator* operate,  Response *response, int msec, int RFIDMilliDegrees, int FCMilliDegrees);
public:
    inline int RFIDMilliDegrees()const{return _rfidMilliDegrees;}
    inline int FCMilliDegrees()const{return _fcMilliDegrees;}
protected:
    bool package(QByteArray& arr) override;
    bool packageToResponse(QByteArray& arr) override;
private:
    int _rfidMilliDegrees;
    int _fcMilliDegrees;
};

#endif // SAMPLEHEATERCALCULATEPOINT_COMMAND_H
