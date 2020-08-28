#include "applicationexception.h"

ApplicationException::ApplicationException():_errMsg("")
{

}

ApplicationException::ApplicationException(const QString &errMsg):_errMsg(errMsg)
{

}

char const *ApplicationException::what() const
{
    return _errMsg.toStdString().c_str();
}
