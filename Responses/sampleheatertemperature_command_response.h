#ifndef SAMPLEHEATERTEMPERATURE_COMMAND_RESPONSE_H
#define SAMPLEHEATERTEMPERATURE_COMMAND_RESPONSE_H
#include "response.h"

class SampleHeaterTemperature_Command_Response : public Response
{
public:
    SampleHeaterTemperature_Command_Response();
    SampleHeaterTemperature_Command_Response(int milli_degrees_C);
public:
    inline int MilliDegreeC()const{return _milliDegreesC;}
private:
    int _milliDegreesC;
};
Q_DECLARE_METATYPE(SampleHeaterTemperature_Command_Response)
#endif // SAMPLEHEATERTEMPERATURE_COMMAND_RESPONSE_H
