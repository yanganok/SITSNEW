#ifndef SETTINGSGET_COMMAND_RESPONSE_H
#define SETTINGSGET_COMMAND_RESPONSE_H
#include "response.h"

class SettingsGet_Command_Response : public Response
{
public:
    SettingsGet_Command_Response();
    SettingsGet_Command_Response(const QString& value);
public:
    inline const QString& value()const{return _value;}
private:
    QString _value;
};
Q_DECLARE_METATYPE(SettingsGet_Command_Response)
#endif // SETTINGSGET_COMMAND_RESPONSE_H
