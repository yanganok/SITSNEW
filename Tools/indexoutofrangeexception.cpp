#include "indexoutofrangeexception.h"

IndexOutOfRangeException::IndexOutOfRangeException()
{

}

IndexOutOfRangeException::IndexOutOfRangeException(const QString &errMsg):_errMsg(errMsg)
{

}

char const *IndexOutOfRangeException::what() const
{
    return _errMsg.toStdString().c_str();
}
