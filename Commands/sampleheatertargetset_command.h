#ifndef SAMPLEHEATERTARGETSET_COMMAND_H
#define SAMPLEHEATERTARGETSET_COMMAND_H
#include "command.h"

class SampleHeaterTargetSet_Command : public Command
{
    Q_OBJECT
public:
    SampleHeaterTargetSet_Command();
    SampleHeaterTargetSet_Command(InstrumentOperator* operate,  Response *response, int msec, int milli_degrees_C);
public:
    inline int MilliDegreeC()const{return _milliDegreesC;}
protected:
    bool package(QByteArray& arr) override;
    bool packageToResponse(QByteArray& arr) override;
private:
    int _milliDegreesC;
};

#endif // SAMPLEHEATERTARGETSET_COMMAND_H
