#ifndef AUDIO_COMMAND_H
#define AUDIO_COMMAND_H
#include "command.h"
/**
* @projectName   SITS
* @brief         音响命令
* @author        YangAn
* @date          2020-06-29
* @Email         yangan@AutoBio.com.cn
*/
class Audio_Command:public Command
{
    Q_OBJECT
public:
    Audio_Command();
    //Audio_Command(InstrumentOperator* operate,  Response *response, int msec);
    Audio_Command(InstrumentOperator* operate,  Response *response, int msec, bool on_off);
protected:
    bool package(QByteArray& arr) override;
    bool packageToResponse(QByteArray& arr);
public:
    inline void setOn_Off(bool value){ _on_Off = value;}
    inline bool on_Off()const {return _on_Off;}
private:
    bool _on_Off;
};
#endif // AUDIO_COMMAND_H
