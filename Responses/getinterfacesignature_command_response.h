#ifndef GETINTERFACESIGNATURE_COMMAND_RESPONSE_H
#define GETINTERFACESIGNATURE_COMMAND_RESPONSE_H
#include "response.h"

class GetInterfaceSignature_Command_Response:Response
{
public:
    GetInterfaceSignature_Command_Response();
    GetInterfaceSignature_Command_Response(const QString &signature);
    inline QString signature()const{return  _signature;}
private:
    QString _signature;
};
Q_DECLARE_METATYPE(GetInterfaceSignature_Command_Response)
#endif // GETINTERFACESIGNATURE_COMMAND_RESPONSE_H
