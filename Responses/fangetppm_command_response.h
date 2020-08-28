#ifndef FANGETPPM_COMMAND_RESPONSE_H
#define FANGETPPM_COMMAND_RESPONSE_H
#include "response.h"

class FanGetPPM_Command_Response : public Response
{
public:
    FanGetPPM_Command_Response();
    FanGetPPM_Command_Response(quint32 ppm);
public:
    inline quint32 ppm()const{return _ppm;}
private:
    quint32 _ppm;
};
Q_DECLARE_METATYPE(FanGetPPM_Command_Response)
#endif // FANGETPPM_COMMAND_RESPONSE_H
