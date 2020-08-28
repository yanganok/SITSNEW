#ifndef SETTINGSGET_COMMAND_H
#define SETTINGSGET_COMMAND_H
#include "command.h"

class SettingsGet_Command : public Command
{
    Q_OBJECT
public:
    SettingsGet_Command();
    SettingsGet_Command(InstrumentOperator* operate,  Response *response, int msec, const QString& keyName);
public:
    inline const QString& keyName()const{return _keyName;}
protected:
    bool package(QByteArray& arr) override;
    bool packageToResponse(QByteArray& arr) override;
private:
    QString _keyName;
};

#endif // SETTINGSGET_COMMAND_H
