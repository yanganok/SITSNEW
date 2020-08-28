#ifndef MISCFWIDS_COMMAND_RESPONSE_H
#define MISCFWIDS_COMMAND_RESPONSE_H
#include "response.h"

class MiscFWIds_Command_Response : public Response
{
public:
    MiscFWIds_Command_Response();
    MiscFWIds_Command_Response(QVector<QString> &names);
public:
    inline const QVector<QString> &names()const{return _names;}
private:
    QVector<QString> _names;
};

#endif // MISCFWIDS_COMMAND_RESPONSE_H
