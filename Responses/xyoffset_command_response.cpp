#include "xyoffset_command_response.h"

XYOffset_Command_Response::XYOffset_Command_Response()
{
    _typeName = classtype();
}

XYOffset_Command_Response::XYOffset_Command_Response(int previous_x_nm, int previous_y_nm)
    :_previous_x_nm(previous_x_nm), _previous_y_nm(previous_y_nm)
{
    _typeName = classtype();
}

