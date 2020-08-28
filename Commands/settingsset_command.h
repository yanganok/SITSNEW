#ifndef SETTINGSSET_COMMAND_H
#define SETTINGSSET_COMMAND_H
#include "command.h"

class SettingsSet_Command : public Command
{
    Q_OBJECT
public:
    SettingsSet_Command();
    SettingsSet_Command(InstrumentOperator* operate,  Response *response, int msec, const QString& keyName, const QString& value);
public:
    inline const QString& keyName()const{return _keyName;}
    inline const QString& value()const{return _value;}
protected:
    bool package(QByteArray& arr) override;
    bool packageToResponse(QByteArray& arr) override;
private:
    QString _keyName;
    QString _value;
};

#endif // SETTINGSSET_COMMAND_H
