#ifndef MISCFWSTAGE_COMMAND_H
#define MISCFWSTAGE_COMMAND_H
#include "command.h"

class MiscFWStage_Command : public Command
{
    Q_OBJECT
public:
    MiscFWStage_Command();
    MiscFWStage_Command(InstrumentOperator* operate,  Response *response, int msec, QString fileName);
public:
    inline const QString& fileName()const{return _fileName;}
protected:
    bool package(QByteArray& arr) override;
    bool packageToResponse(QByteArray& arr) override;
private:
    QString _fileName;
};

#endif // MISCFWSTAGE_COMMAND_H
