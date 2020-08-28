#include "getinterfacesignature_command_response.h"

GetInterfaceSignature_Command_Response::GetInterfaceSignature_Command_Response()
{
    _typeName = classtype();
}

GetInterfaceSignature_Command_Response::GetInterfaceSignature_Command_Response(const QString &signature)
    :_signature(signature)
{
    _typeName = classtype();
}
