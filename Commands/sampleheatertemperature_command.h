#ifndef SAMPLEHEATERTEMPERATURE_COMMAND_H
#define SAMPLEHEATERTEMPERATURE_COMMAND_H
#include "command.h"

class SampleHeaterTemperature_Command:public Command
{
    Q_OBJECT
public:
    SampleHeaterTemperature_Command();
    SampleHeaterTemperature_Command(InstrumentOperator* operate,  Response *response, int msec, bool flowcell_RTD);
public:
    inline bool flowcell_RTD()const{return _flowcell_RTD;}
protected:
    bool package(QByteArray& arr) override;
    bool packageToResponse(QByteArray& arr) override;
private:
    bool _flowcell_RTD;
};

#endif // SAMPLEHEATERTEMPERATURE_COMMAND_H
