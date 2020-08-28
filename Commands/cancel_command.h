#ifndef CANCEL_COMMAND_H
#define CANCEL_COMMAND_H
#include "command.h"

class Cancel_Command : public Command
{
    Q_OBJECT
public:
    Cancel_Command();
    Cancel_Command(InstrumentOperator* operate,  Response *response, int msec, const QString cancel_cmd_name);
    QString cancel_cmd_name() const;

protected:
    bool package(QByteArray& arr) override;
    bool packageToResponse(QByteArray& arr) override;
private:
    QString _cancel_cmd_name;
};

#endif // CANCEL_COMMAND_H
