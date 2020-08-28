#ifndef LOGRECORD_COMMAND_RESPONSE_H
#define LOGRECORD_COMMAND_RESPONSE_H
#include "response.h"

class LogRecord_Command_Response:Response
{
public:
    LogRecord_Command_Response();
    LogRecord_Command_Response(QVector<QString> records);
public:
    inline const QVector<QString>& records()const{return _records;}
private:
    QVector<QString> _records;
};
Q_DECLARE_METATYPE(LogRecord_Command_Response)
#endif // LOGRECORD_COMMAND_RESPONSE_H
