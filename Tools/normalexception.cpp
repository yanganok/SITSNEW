#include "normalexception.h"

NormalException::NormalException()
{

}

NormalException::NormalException(const QString &errMsg)
    :_errMsg(errMsg)
{

}

const char *NormalException::what() const
{
    return _errMsg.toStdString().c_str();
}
