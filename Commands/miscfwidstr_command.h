#ifndef MISCFWIDSTR_COMMAND_H
#define MISCFWIDSTR_COMMAND_H
#include "command.h"

class MiscFWIdStr_Command:public Command
{
    Q_OBJECT
public:
    MiscFWIdStr_Command();
    MiscFWIdStr_Command(InstrumentOperator* operate,  Response *response, int msec, QString fwId);
public:
    inline const QString &fwId(){return _fwId;}
protected:
    bool package(QByteArray& arr) override;
    bool packageToResponse(QByteArray& arr) override;
private:
    QString _fwId;
};

#endif // MISCFWIDSTR_COMMAND_H
