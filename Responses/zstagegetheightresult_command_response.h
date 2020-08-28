#ifndef ZSTAGEGETHEIGHTRESULT_COMMAND_H
#define ZSTAGEGETHEIGHTRESULT_COMMAND_H
#include "response.h"

class ZStageGetHeightResult_Command_Response : public Response
{
public:
    ZStageGetHeightResult_Command_Response();
    ZStageGetHeightResult_Command_Response(bool success, int height_nm);
public:
    inline bool success()const{return _success;}
    inline int height_nm()const{return  _height_nm;}
private:
    bool _success;
    int _height_nm;
};
Q_DECLARE_METATYPE(ZStageGetHeightResult_Command_Response)
#endif // ZSTAGEGETHEIGHTRESULT_COMMAND_H
