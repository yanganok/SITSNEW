#include "response.h"
#include <utility>
#include <qdebug.h>
Response::Response():
    _msg(""), _recDate(QDateTime::currentDateTime()),_cmdId(0)
{
    _typeName = classtype();
}

Response::Response(int cmdId, QString key):
    _msg(""), _recDate(QDateTime::currentDateTime()),_cmdId(cmdId)
{
    _typeName = classtype();
    _key = key;
}

const QString Response::classtype() const
{
    return QString::fromStdString(typeid(*this).name()).mid(6);
}
