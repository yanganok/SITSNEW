#ifndef SETTINGSGETKEYNAMES_COMMAND_RESPONSE_H
#define SETTINGSGETKEYNAMES_COMMAND_RESPONSE_H
#include "response.h"
#include <QVector>

class SettingsGetKeyNames_Command_Response : public Response
{
public:
    SettingsGetKeyNames_Command_Response();
    SettingsGetKeyNames_Command_Response(QVector<QString>& names);
public:
    inline const QVector<QString>& name()const{return _names;}
private:
    QVector<QString> _names;
};
Q_DECLARE_METATYPE(SettingsGetKeyNames_Command_Response)
#endif // SETTINGSGETKEYNAMES_COMMAND_RESPONSE_H
