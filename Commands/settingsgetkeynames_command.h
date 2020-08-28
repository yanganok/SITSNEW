#ifndef SETTINGSGETKEYNAMES_H
#define SETTINGSGETKEYNAMES_H
#include "command.h"

class SettingsGetKeyNames_Command : public Command
{
    Q_OBJECT
public:
    SettingsGetKeyNames_Command();
    SettingsGetKeyNames_Command(InstrumentOperator* operate,  Response *response, int msec, const QString& subString);
public:
    inline const QString& subString()const{return _subString;}
protected:
    bool package(QByteArray& arr) override;
    bool packageToResponse(QByteArray& arr) override;
private:
    QString _subString;
};

#endif // SETTINGSGETKEYNAMES_H
