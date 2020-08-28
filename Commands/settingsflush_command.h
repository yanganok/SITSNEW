#ifndef SETTINGSFLUSH_COMMAND_H
#define SETTINGSFLUSH_COMMAND_H
#include "command.h"

class SettingsFlush_Command : public Command
{
    Q_OBJECT
public:
    SettingsFlush_Command();
    SettingsFlush_Command(InstrumentOperator* operate,  Response *response, int msec);
protected:
    bool package(QByteArray& arr) override;
    bool packageToResponse(QByteArray& arr) override;
};

#endif // SETTINGSFLUSH_COMMAND_H
