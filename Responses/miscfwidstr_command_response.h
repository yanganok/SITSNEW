#ifndef MISCFWIDSTR_COMMAND_RESPONSE_H
#define MISCFWIDSTR_COMMAND_RESPONSE_H
#include "response.h"

class MiscFWIdStr_Command_Response : public Response
{
public:
    MiscFWIdStr_Command_Response();
    MiscFWIdStr_Command_Response(QString fwId);
public:
    inline const QString& fwId()const{return _fwId;}
private:
    QString _fwId;
};
Q_DECLARE_METATYPE(MiscFWIdStr_Command_Response)
#endif // MISCFWIDSTR_COMMAND_RESPONSE_H
