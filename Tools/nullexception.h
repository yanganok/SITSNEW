#ifndef NULLEXCEPTION_H
#define NULLEXCEPTION_H
#include <QException>

class NullException : public QException
{
public:
    NullException();
    NullException(const QString& errMsg);
public:
    char const* what()const  override;
    inline const QString &errMsg()const{return _errMsg;}
private:
    QString _errMsg;
};

#endif // NULLEXCEPTION_H
