#ifndef NORMALEXCEPTION_H
#define NORMALEXCEPTION_H
#include <QException>

class NormalException : public QException
{
public:
    NormalException();
    NormalException(const QString& errMsg);
    char const* what()const  override;
    inline const QString &errMsg()const{return _errMsg;}
private:
    QString _errMsg;
};

#endif // NORMALEXCEPTION_H
