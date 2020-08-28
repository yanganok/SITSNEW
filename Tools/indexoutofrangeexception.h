#ifndef INDEXOUTOFRANGEEXCEPTION_H
#define INDEXOUTOFRANGEEXCEPTION_H
#include <QException>

class IndexOutOfRangeException : public QException
{
public:
    IndexOutOfRangeException();
    IndexOutOfRangeException(const QString& errMsg);
public:
    char const* what()const  override;
    inline const QString &errMsg()const{return _errMsg;}
private:
    QString _errMsg;
};

#endif // INDEXOUTOFRANGEEXCEPTION_H
