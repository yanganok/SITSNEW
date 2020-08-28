#ifndef XYSETMINMOVEMSEC_COMMAND_RESPONSE_H
#define XYSETMINMOVEMSEC_COMMAND_RESPONSE_H
#include "response.h"

class XYSetMinMoveMsec_Command_Response : public Response
{
public:
    XYSetMinMoveMsec_Command_Response();
    XYSetMinMoveMsec_Command_Response(quint32 moveMsec);
public:
    inline quint32 moveMsec()const{return  _moveMsec;}
private:
    quint32 _moveMsec;
};
Q_DECLARE_METATYPE(XYSetMinMoveMsec_Command_Response)
#endif // XYSETMINMOVEMSEC_COMMAND_RESPONSE_H
