#ifndef SAMPLEHEATERTARGETGET_COMMAND_RESPONSE_H
#define SAMPLEHEATERTARGETGET_COMMAND_RESPONSE_H
#include "response.h"

class SampleHeaterTargetGet_Command_Response : public Response
{
public:
    SampleHeaterTargetGet_Command_Response();
    SampleHeaterTargetGet_Command_Response(int milli_degrees_C);
public:
    inline int MilliDegreeC()const{return _milliDegreesC;}
private:
    int _milliDegreesC;
};

#endif // SAMPLEHEATERTARGETGET_COMMAND_RESPONSE_H
