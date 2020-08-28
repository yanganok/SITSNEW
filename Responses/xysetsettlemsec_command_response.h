#ifndef XYSETSETTLEMSEC_COMMAND_RESPONSE_H
#define XYSETSETTLEMSEC_COMMAND_RESPONSE_H
#include "response.h"

class XYSetSettleMsec_Command_Response:public Response
{
public:
    XYSetSettleMsec_Command_Response();
    XYSetSettleMsec_Command_Response(quint32 moveMsec);
public:
    inline quint32 moveMsec()const{return  _moveMsec;}
private:
    quint32 _moveMsec;
};
Q_DECLARE_METATYPE(XYSetSettleMsec_Command_Response)

#endif // XYSETSETTLEMSEC_COMMAND_RESPONSE_H
