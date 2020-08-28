#ifndef LOGGETLIST_COMMAND_RESPONSE_H
#define LOGGETLIST_COMMAND_RESPONSE_H
#include "response.h"

class LogGetList_Command_Response : public Response
{
public:
    LogGetList_Command_Response();
    LogGetList_Command_Response(QVector<QString>& names);
public:
    inline const QVector<QString> &names()const{return _names;}
private:
    QVector<QString> _names;
};
Q_DECLARE_METATYPE(LogGetList_Command_Response)
#endif // LOGGETLIST_COMMAND_RESPONSE_H
