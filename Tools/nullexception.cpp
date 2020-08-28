#include "nullexception.h"

NullException::NullException()
{

}

NullException::NullException(const QString &errMsg):_errMsg(errMsg)
{

}

char const *NullException::what() const
{
    return _errMsg.toStdString().c_str();
}
