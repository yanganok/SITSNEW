#ifndef XYOFFSET_COMMAND_RESPONSE_H
#define XYOFFSET_COMMAND_RESPONSE_H
#include "response.h"

class XYOffset_Command_Response : public Response
{
public:
    XYOffset_Command_Response();
    XYOffset_Command_Response(int previous_x_nm, int previous_y_nm);
public:
    inline int previous_x_nm()const{return _previous_x_nm;}
    inline int previous_y_nm()const{return _previous_y_nm;}

private:
    int _previous_x_nm;
    int _previous_y_nm;
};
Q_DECLARE_METATYPE(XYOffset_Command_Response)
#endif // XYOFFSET_COMMAND_RESPONSE_H
