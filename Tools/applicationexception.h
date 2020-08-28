#ifndef APPLICATIONEXCEPTION_H
#define APPLICATIONEXCEPTION_H
#include <QException>
#include <QString>

class ApplicationException : public QException
{
public:
    ApplicationException();
    ApplicationException(const QString& errMsg);
public:
    char const* what()const  override;
    inline const QString &errMsg()const{return _errMsg;}
private:
    QString _errMsg;
};

#endif // APPLICATIONEXCEPTION_H
