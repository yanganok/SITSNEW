#ifndef ENUMS_H
#define ENUMS_H
#include <QObject>
#include "onOff.h"
namespace Global {
    enum class TAG:quint16{
        NEWSUBFILETYPE = 254,
        SUBFILETYPE,
        IMAGEWIDTH,
        IMAGELENGTH,
        BITSPERSAMPLE,
        COMPRESSION,
        PHOTOMETRICINTERPRETATION = 262,
        THRESHHOLDING,
        CELLWIDTH,
        CELLLENGTH,
        FILLORDER,
        DOCUMENTNAME = 269,
        IMAGEDESCRIPTION,
        MAKE,
        MODEL,
        STRIPOFFSETS,
        ORIENTATION,
        SAMPLESPERPIXEL = 277,
        ROWSPERSTRIP,
        STRIPBYTECOUNTS,
        MINSAMPLEVALUE,
        MAXSAMPLEVALUE,
        XRESOLUTION,
        YRESOLUTION,
        PLANARCONFIGURATION,
        PAGENAME,
        XPOSITION,
        YPOSITION,
        FREEOFFSETS,
        FREEBYTECOUNTS,
        GRAYRESPONSEUNIT,
        GRAYRESPONSECURVE,
        T4OPTIONS,
        T6OPTIONS,
        RESOLUTIONUNIT = 296,
        PAGENUMBER,
        TRANSFERFUNCTION = 301,
        SOFTWARE = 305,
        DATETIME,
        ARTIST = 315,
        HOSTCOMPUTER,
        PREDICTOR,
        WHITEPOINT,
        PRIMARYCHROMATICITIES,
        COLORMAP,
        HALFTONEHINTS,
        TILEWIDTH,
        TILELENGTH,
        TILEOFFSETS,
        TILEBYTECOUNTS,
        INKSET = 332,
        INKNAMES,
        NUMBEROFINKS,
        DOTRANGE = 336,
        TARGETPRINTER,
        EXTRASAMPLES,
        SAMPLEFORMAT,
        SMINSAMPLEVALUE,
        SMAXSAMPLEVALUE,
        TRANSFERRANGE,
        JPEGPROC = 512,
        JPEGINTERCHANGEFORMAT,
        JPEGINTERCHANGEFORMATLNGTH,
        JPEGRESTARTINTERVAL,
        JPEGLOSSLESSPREDICTORS = 517,
        JPEGPOINTTRANSFORMS,
        JPEGQTABLES,
        JPEGDCTABLES,
        JPEGACTABLES,
        YCBCRCOEFFICIENTS = 529,
        YCBCRSUBSAMPLING,
        YCBCRPOSITIONING,
        REFERENCEBLACKWHITE,
        COPYRIGHT = 33432,
        AUTOBIOTAG1 = 50506,
        AUTOBIOTAG2
    };
    enum class Type:quint16{
        BYTE = 1,
        ASCII,
        SHORT,
        LONG,
        RATIONAL,
        SBYTE,
        UNDEFINED,
        SSHORT,
        SLONG,
        SRATIONAL,
        FLOAT,
        DOUBLE
    };
}
namespace Image_Module {
    enum class ImageRotation{
        DEGREES0,
        DEGREES90,
        DEGREES180,
        DEGREES270,
        DEGREES90FLIPVERTICAL,
        DEGREES270FLIPVERTICAL
    };
    enum class ChangeType{
        NONE = 0,
        ValidRowsChanged = 1,
        DataChanged = 2
    };
    enum class ImageFormat{
        JPEG,
        PNG,
        TIFF
    };
    enum class OverwriteHandling{
        THROWEXCEPTION,
        OVERWRITE,
        BACKUPCURRENTFILEFIRST,
        RENAMENEW
    };
    enum class COMPRESSION{
        UNCOMPRESSED = 1,
        CCITT1D,
        GROUP3FAX,
        GROUP4FAX,
        LZW,
        JPEG,
        PACKBITS = 32773
    };
}
namespace Camera_Module {
    /**
     * @brief The CameraZAlgorithm enum Z算法
     */
    enum class CameraZAlgorithm{
        EXACT,
        AF,
        OFFSET
    };
    /**
     * @brief The CameraDataMode enum 相机数据类型
     */
    enum class CameraDataType{
        RAW,
        MEMFILL,
        GARBAGE,
        HORIZ_GRADIENT,
        VERT_GRADIENT,
        DIAG_GRADIENT,
        CLASSIC,
        WALKING,
        MONO_HORIZ_BARS,
        MONO_VERT_BARS,
        COLOR_VERT_BARS
    };
    /**
     * @brief The CameraChannelType enum 相机通道类型
     */
    enum class CameraChannelType{
        NONE,
        RED,
        GREEN,
        LASER = 4,
    };
    /**
     * @brief The CameraEvent enum 相机事件
     */
    enum class CameraEvent{
        SNAP,
        XYMOVE,
        ZMOVE,
        AFCALCULATE,
        SENSORCAPTURE,
    };
}

namespace Flowcell_Module {
    /**
     * @brief The FlowcellDoorState enum Flowcell门状态
     */
    enum class FlowcellDoorState{
        OPEN,
        CLOSED,
        MIDWAY
    };
}

namespace Fluidics_Module {


    enum class ValvePosition:quint8
    {
        POSITION_FIRST = 1,
        POSITION_SECOND = 2,
        POSITION_THIRD = 3,
        POSITION_FOURTH = 4,
        POSITION_FIFTH = 5,
        POSITION_SIXTH = 6,

    };
    /**
     * @brief The FluidicsAutomationOperate enum 液路自动操作类型
     */
    enum class FluidicsAutomationOperate{
        INIT,
        LOAD,
        PIERCE,
        UNPIERCE,
        SEQUENCE,
        WASH,
        UNLOAD,
        BSMUP,
        BSMDOWN,
        SHIP,
    };
    /**
     * @brief The FluidicsAutomationPosition enum 液路自动操作位置
     */
    enum class FluidicsAutomationPosition{
        UNKNOWN,
        FRONT,
        PICK,
        DROP,
        SIPPER_HOME,
        SEQUENCE,
        FLOWCELL_HOME,
        PREDOCK,
        DOCK,
        WASH,
        UNLOAD,
        LOAD,
        UNPIERCE
    };
}

namespace RFID_Module {
    /**
     * @brief The RFIDTagId enum RFID标签
     */
    enum class RFIDTagId{
        FLOWCELL,
        BOTTLE,
        REAGENT
    };
    /**
     * @brief The RFIDTagStatus enum RFID标签状态
     */
    enum class RFIDTagStatus{
        STALE,
        CLEAN,
        DIRTY
    };
}

namespace Sensor_Module {
    /**
     * @brief The SensorType enum 传感器类型
     */
    enum class SensorType
    {
        LIQUIDROADPRESSURE,
        FLOWCELL_HOME_X,
        FLOWCELL_HOME_Y,
        FLOWCELL_HOME_Z,
        FLOWCELL_HOME_ALIGN,
        FLOWCELL_ALIGN1,
        FLOWCELL_ALIGN2,
        FLOWCELL_DOOR_OPEN,
        FLOWCELL_DOOR_CLOSED,
        REAGENT_TRAY_DOWN,
        REAGENT_TRAY_SEQ,
        REAGENT_TRAY_UP,
        REAGENT_DOOR_OPEN,
        REAGENT_TRAY_BACK,
        REAGENT_TRAY_PRESENT,
        SIPPER_Y_HOME,
        SIPPER_Y_FWD,
        STRAWS_UP,
        STRAWS_DOWN,
        BUBBLE0,
        BUBBLE1,
        BUBBLE2,
        BUBBLE3,
        BUBBLE4,
        BUBBLE5,
        WASTE_PRESENT,
        WASTE_DOOR_OPEN,
        WASTE_FULL,
        BUFFER_PRESENT,
        PANEL_PRESENT,
        POWER_BUTTON,
        DUMMY
    };
    enum class SensorAixs{
        SIPPER_Y,
        FLOWCELL_Y,
        FLOWCELL_X,
        FLOWCELL_Z,
        FLOWCELL_ALIGN,
        FLOWCELL_DOOR,
        REAGENT_Z,
        STRAW_Z
    };
    enum class TemperatureSensor{
        BOARD0,
        BOARD1,
        THERMOCOUPLE0,
        THERMOCOUPLE1,
        CAMERA0,
        CAMERA1,
        CAMERA2,
        CAMERA3,
        CAMERA4,
        CAMERA5
    };
}

namespace MotionAixs_Module {
    /**
    * @brief The Motion_Axis enum 运动平台轴坐标
    */
    enum class Motion_Axis{
        SIPPER_Y,
        FLOWCELL_Y,
        FLOWCELL_X,
        FLOWCELL_Z,
        FLOWCELL_ALIGN,
        FLOWCELL_DOOR,
        REAGENT_Z,
        STRAW_Z
    };
    enum class Motion_Result{
        NA,
        OKAY,
        ERROR_POSITION,
        ERROR_SPEED,
        ERROR_PAIR,
        ERROR_SAFETY,
        UNKNOWN
    };
}

namespace Peripheral_Eauipment {
    /**
     * @brief The FanType enum 风扇类型
     */
    enum class FanType{
        LED,
        EBOX0,
        EBOX1,
        FLOWCELL,
        EXHAUST0,
        EXHAUST1,
        EXHAUST2

    };
}

namespace CommunicateCoreUpper {
    /**
     * @brief The CommandStatus enum 当前命令的状态
     */
    enum class CommandStatus{
        READY_SEND,//组包完成待发送
        SENDED,//发送包
        RESPONSE,//收到回应
        RECEIVED,//收到数据
        COMMAND_FAULT,//默认命令
    };
}
namespace CommunicateCoreUnderlying {
    /**
     * @brief The CommunicateStatus enum 通讯状态
     */
    enum class CommunicateStatus{
        OPENED,
        CLOSE,
        ISNOTEXISTS,
        OCCUPY
    };
    /**
     * @brief 命令类型
     */
    enum class CommandType:quint8{
        SEND        = 0x01,
        RESPONSE    = 0x02,
        RECEIVED    = 0x03,
    };
    /**
     * @brief The DevicType enum 设置类型
     */
    enum class DevicType:quint8{
        DE_TP_DISTRIBUTION_VALVE        = 0x00,    //分配阀                          0x00
        DE_TP_SYRINGE                   = 0x01,               		//注射泵                          0x01
        //DE_TP_COOLING_PUMP            = 0x02,           	//冷却泵                          0x02
        //DE_TP_VACUUM_PUMP             = 0x03,           		//真空泵                          0x03
        DE_TP_EV                        = 0x04,                     		//电磁阀                          0x04
        //DE_TP_BUBBLE_REMOVAL          = 0x05,         	//除气泡装置                       0x05

        //DE_TP_CAMERA                  = 0x06,                 	//相机                            0x06
        DE_TP_LED                       = 0x07,                    		//LED                             0x07
        DE_TP_LD                        = 0x08,                     		//LD                              0x08
        DE_TP_FCTC                      = 0x09,  		//FC温控模块                        0x09
        DE_TP_fcLEVEL_xyPLATFORM        = 0x0A,     		//FC调平,XY平台                     0x0A
        DE_TP_VCM                       = 0x0B,                    		//音圈电机                          0x0B
        //DE_TP_PCUM                    = 0x0C,                   	//压电陶瓷超声电机                      0x0C
        //DE_TP_BDC                     = 0x0D,                    	//直流有刷电机                        0x0D
        //DE_TP_BLDC                    = 0x0E,                   	//直流无刷电机                        0x0E
        //DE_TP_STM                     = 0x0F,                    	//步进电机                            0x0F
        DE_TP_LP                        = 0x10,                     		//液路压力传感器                       0x10
        DE_TP_BUBBLE                    = 0x11,                 	//气泡检测传感器                       0x11
        //DE_TP_RFID                    = 0x12,                   	//RFID模块                            0x12
        //DE_TP_LIGHT_STRIP             = 0x13,            	//灯带                                0x13
        //DE_TP_GPIO                    = 0x14,                   	//通用输入输出口                       0x14
        //DE_TP_TEMPERATURE             = 0x15,            	//温湿度传感器                        0x15
        DE_TP_FAN                       = 0x16,                    		//机箱风扇                            0x16

        DE_unTP_raBWLRPU                = 0x17,                   //液路自动化之缓冲液/废液回收处理单元      0x17
        DE_unTP_raRAPU                  = 0x18,                     //液路自动化之试剂装配处理单元            0x18
        //DE_unTP_raRDPU                = 0x19,                   //液路自动化之试剂分配处理单元            0x19
        //DE_unTP_compPU                = 0x1A,                   //相机光学运动平台处理单元                0x1A
        //DE_unTP_fcAPU                 = 0x1B,                    // FC自动化处理单元                     0x1B
        //DE_unTP_ctmPU                 = 0x1C,                    //机箱温度管理处理单元                   0x1C
        //DE_unTP_psmPU                 = 0x1D,                    //电源供电管理处理单元                   0x1D

        //DE_functionTP_initOp          = 0x1E,           	//功能模块初始化操作                     0x1E
        //DE_functionTP_selfTestOp      = 0x1F,        	//功能模块自检操作                       0x1F
        //DE_functionTP_sequencingOp    = 0x20,      	//功能模块测序操作                       0x20
        //DE_functionTP_washOp          = 0x21,            	//功能模块清洗操作                       0x20
        //DE_functionTP_pressureTestOp  = 0x22,    	//功能模块压力测试操作                    0x22
        //DE_functionTP_ConfigurationOp = 0x23,   	//功能模块配置操作                       0x23
    };

    enum class ValveDeviceId{
        VALVE1=1,                //转动到位置n（n=1...10）
        VALVE2=2,                //获得阀当前位置
        All = 3,
        NONE = 0
    };
    /**
     * @brief The ValveControlWord enum 分配阀控制字
     */
    enum class ValveControlWord{
        CW_VALVE_GO=1,                //转动到位置n（n=1...10）
        CW_VALVE_CP=2,                //获得阀当前位置
        //CW_VALVE_S_NP=3,            //设置阀的位置数
        //CW_VALVE_G_NP=4,            //获得阀的位置数
        //CW_VALVE_GO_HOME=5,         //将阀门回到HOME（原点）位  此命令帝肯泵独有
        //CW_VALVE_R=6,               //读取固件修改
        CW_VALVE_E=7,                 //读取最新阀门错误代码
        //CW_VALVE_D=8,               //读取阀门命令模式
        CW_VALVE_INIT=9,              //设备初始化
        //CW_VALVE_SET=10,            //参数设置
        CW_VALVE_POWER_OPEN=11,       //设备打开/关闭 （参数=0xff时，打开，=0x00时，关闭）电源打开/关闭
        CW_VALVE_POWER_CLOSE=12,      //设备打开/关闭 （参数=0xff时，打开，=0x00时，关闭）电源打开/关闭
        CW_VALVE_GET_ST=13,           //获得设备状态
    };

    /**
     * @brief The ValveStatusWord enum 分配阀状态字
     */
    enum class ValveStatusWord{
        stVALVE_ACK=1,                        //阀命令正确应答
        stVALVE_BUSY=2,                       //阀正忙
        stVALVE_ZERO_ERROR=3,                 //0x63,阀门故障（阀门不能归原点）
        stVALVE_NVM_ERROR=4,                  //0x58,非易失性存储器错误
        stVALVE_CFG_ERROR=5,                  //0x4D,阀门配置错误或命令模式错误
        stVALVE_POS_ERROR=6,                  //0x42,阀门定位错误
        stVALVE_DATA_IT_ERROR=7,              //0x37,数据完整性错误
        stVALVE_DATA_CRC_ERROR=8,             //0x2C,数据CRC错误
        stVALVE_AOR=9,                        //Abnormality of response  应答异常
        stVALVE_STOP=10,                      //分配阀停止运行（电源关闭）
        sVALVE_RUN=11,                        //分配阀开始运行（电源打开）
        sVALVE_POWER_OPEN=12,                 //分配阀电源打开
        sVALVE_POWER_CLOSE=13,                //分配阀电源打开
    };

    /**
     * @brief The SyringPumpControlWord enum 注射泵控制字
     */
    enum class SyringPumpControlWord{
        //CW_SYRINGE_TOP=1,                //移动到顶部(HOME点)，绝对位置0，阀门位置（排出）
        CW_SYRINGE_MOVE=1,             //泵绝对体积操作
        CW_SYRINGE_BOTTOM=2,              //移动到底部绝对位置24000（吸入）
        CW_SYRINGE_CURRENT_INn=3,       //从当前位置吸入n ul (三通阀用O命令,阀得电)
        CW_SYRINGE_CURRENT_OUTn=4,      //从当前位置排出n ul (三通阀用I命令，阀断电)
        CW_SYRINGE_INn=5,               //从0点(初始位置，顶部)吸入 n ul
        CW_SYRINGE_OUTn=6,              //排空（从当前任意位置，把液体全部泵出，回到绝对位置0）
        CW_SYRINGE_SET_V_IN=7,          //设置吸入速度
        CW_SYRINGE_SET_V_OUT=8,         //设置排出速度
        CW_SYRINGE_INIT=9,              //初始化注射泵(回HOME点，绝对位置0，阀断电)
        CW_SYRINGE_OPEN=10,              //设备打开/关闭 （参数=0xff时，打开，=0x00时，关闭）
        CW_SYRINGE_POSION=11,            //读取注射器绝对位置
        CW_SYRINGE_GET_RUN_ST=12,        //获得设备运行状态(针对注射泵设备的状态查询与 CW_SYRINGE_GET_BUSY_ST 不同)
        CW_SYRINGE_GET_BUSY_ST=13,       //获得设备是否忙的状态（当设备正在运行时，则返回‘@’表示
                                        //正忙，‘ ' ’表示动作结束，准备就绪 ），用/1 命令来查询此状态
        CW_SYRINGE_GET_APositon_ST=14,        //报告绝对柱塞位置
        CW_SYRINGE_GET_START_SPEED_ST=15,     //报告开始速度
        CW_SYRINGE_GET_TOP_SPEED_ST=16,       //报告最高速度
        CW_SYRINGE_GET_CUTOFF_SPEED_ST=17,    //报告截止速度
        CW_SYRINGE_GET_ActulPositon_ST=18,     //报告柱塞的实际位置
        CW_SYRINGE_GET_ValvePositon_ST=19,    //报告阀门位置
        CW_SYRINGE_GET_Bufffer_ST=20,         //报告命令缓冲区状态
        CW_SYRINGE_GET_backlash_ST=21,        //报告间隙增量的数量
        CW_SYRINGE_GET_PumpInit_ST=22,        //报告泵初始化的数量
        CW_SYRINGE_GET_PlungerMove_ST=23,     //报告柱塞移动次数
        CW_SYRINGE_GET_ValveMove_ST=24,       //报告阀门运动次数
        CW_SYRINGE_GET_VML_ST=25,             //报告阀门移动次数（自上次报告以来）
        CW_SYRINGE_GET_FirmwareCHK_ST=26,     //报告固件校验和
        CW_SYRINGE_GET_ValveSensor_ST=27,     //?*    报告阀门传感器的当前值（总是报告255.）
        CW_SYRINGE_GET_FirmwareVersion_ST=28,    //?&    报告固件版本
        CW_SYRINGE_GET_ZeroGap_ST=29,         //?24    报告零间隙增量
        CW_SYRINGE_GET_asQ_ST=30,             //?29    与Q相同（查询，状态和错误字节）
        CW_SYRINGE_GET_PumpCFG_ST=31,         //?76    报告泵配置
        CW_SYRINGE_POWER_OPEN=32,             //打开注射泵电源
        CW_SYRINGE_POWER_CLOSE=33,            //关闭注射泵电源
        CW_SYRINGE_CONFIG_WRITE=34,           //将配置写入寄存器（）   //2020.03.30 添加
        CW_SYRINGE_CONFIG_BPS_9K6=35,         //配置注射泵波特率为9.6KBPS
        CW_SYRINGE_CONFIG_BPS_38K4=36,        //配置注射泵波特率为38.4KBPS
    };

    /**
     * @brief The SyringPumpStatusWord enum 注射泵状态字
     */
    enum class SyringPumpStatusWord:quint32{
        stSY_NO_ERR=0,                        //没有错误
        stSY_FAILED_INIT=1,                   //初始化失败
        stSY_INVALID_CMD=2,                   //无效命令
        stSY_INVALID_PARA=3,                  //无效参数
        stSY_COMM_ERR=4,                      //通信错误
        stSY_INVALID_R=5,                     //无效的‘R’命令
        stSY_VOLTAGE_LOW=6,                   //电源电压过低
        stSY_NOT_INIT=7,                      //设备未初始化
        stSY_PROGRAM_PORGRESS=8,              //程序正在进行中
        stSY_SYRINGE_OVERLOAD=9,              //注射器过载 s
        stSY_VALVE_OVERLOAD=10,               //阀过载
        stSY_SY_MOVE_NOT=11,                  //不允许注射器移动
        stSY_CANNOT_AGAINST_LIMIT=12,         //不能违背极限
        stSY_COMMAND_BUFFER_OVERFLOW=15,      //命令缓冲区溢出
        stSY_USE3WAY_VALVE=16,                //只能用于3通阀
        stSY_LOOPS_NESTED_TOO_DEEP=17,        //嵌套太深的循环
        stSY_PRG_LABEL_NO_FOUND=18,           //未找到程序标签
        stSY_END_PRG_NO_FOUND=19,             //程序结束未找到
        stSY_OUT_PRG_SPACE=20,                //程序空间之外
        stSY_HOME_NO_SET=21,                  //HOME 没有设置
        stSY_TOO_PRG_CALLS=22,                //程序调用太多
        stSY_PRG_NO_FOUND=23,                 //找不到程序
        stSY_VALVE_POSITION_ERR=24,           //阀门位置错误
        stSY_SY_POSITION_CORRUPTED=25,        //注射器位置损坏
        stSY_SY_GO_PAST_HOME=26,              //注射器可以回到HOME
        stSY_SY_RUN_OK=30,                    //注射器运行到位或准备就绪,向注射泵发"/1"有会出现获得这个状态
        stSY_SY_BUSY=31,                      //注射器正在运行或忙,向注射泵发"/1"有会出现获得这个状态
        stSY_SY_POWER_OPEN=32,
        stSY_SY_POWER_CLOSE=33,
    };

    /**
     * @brief The SyringPumpId enum 设备ID号
     */
    enum class SyringPumpId:quint8{
        ALL = 3,
        SYRING1CS = 1,
        SYRING2CS = 2,
        NONE = 0,
    };

    /**
     * @brief The VaccumPumpControlWord enum 真空泵控制字
     */
    enum class VaccumPumpControlWord{
        CW_VACUUM_PUMP_OPEN=1,              //打开真空泵（电源打开）
        CW_VACUUM_PUMP_CLOSE=2,             //关闭真空泵（电源关闭）
        //CW_VACUUM_PUMP_STATE_GET=3,       //获得真空泵运行状态
        //CW_VACUUM_PUMP_INIT=4,            //初始化真空泵
        //CW_VACUUM_PUMP_FAULT_GET=5        //获得故障信息
    };

    /**
     * @brief The VaccumPumpStatusWord enum 真空泵状态字
     */
    enum class VaccumPumpStatusWord{
        st_VACUUM_PUMP_CLOSE=0,    //泵电源关闭
        st_VACUUM_PUMP_OPEN=16,   //真空泵电源开启
    };

    /**
     * @brief The ElectronicValveControlWord enum 电磁阀控制字
     */
    enum class ElectronicValveControlWord{
        CW_EV_OPEN=1,              //打开电磁阀
        CW_EV_CLOSE=2,             //关闭电磁阀
        CW_EV_STATE_GET=3,         //获得电磁阀运行状态
        CW_EV_FAULT_GET=5          //获得故障信息
    };

    /**
     * @brief The ElectronicValveStatusWord enum 电磁阀状态字
     */
    enum class ElectronicValveStatusWord{
        st_EV_CLOSE=0,      //电磁阀关闭
        st_EV_OPEN=1,       //电磁阀打开
        st_EV_ERR=2,        //发生错误
    };

    /**
     * @brief The WipeOffBubbleControlWord enum 除气泡装置控制字
     */
    enum class WipeOffBubbleControlWord{
        CW_BUBBLE_REMOVAL_OPEN=1,              //打开除气泡装置（电源打开）
        CW_BUBBLE_REMOVAL_CLOSE=2,             //打开除气泡装置（电源关闭）
        CW_BUBBLE_REMOVAL_STATE_GET=3,         //获得打开除气泡装置运行状态
        CW_BUBBLE_REMOVAL_INIT=4,              //初始化打开除气泡装置
      //  CW_BUBBLE_REMOVAL_FAULT_GET=5        //获得故障信息
    };

    /**
     * @brief The WipeOffBubbleStatusWord enum 除气泡装置状态字
     */
    enum class WipeOffBubbleStatusWord{
        st_BUBBLE_REMOVAL_CLOSE=0,      //除气泡装置电源关闭
        st_BUBBLE_REMOVAL_OPEN=16,      //除气泡装置电源开启,真空超过控制范围：琥珀色--闪烁
        st_BUBBLE_REMOVAL_CEILING=17,   //真空达到控制上限: 绿色 — 常亮
        st_BUBBLE_REMOVAL_SET_POINT=18, //真空达到控制设置点: 绿色 — 常亮
        st_BUBBLE_REMOVAL_STOP_ERR=19,  //发生错误, 停止运行: 琥珀色 — 常亮
    };

    enum class MeasureFlightTimeBubbleControlWord:quint8{
        CW_BUBBLE_MEASURE_TIME = 0x09,
        CW_BUBBLE_ENDMEASURE_TIME = 0x02,
    };

    enum class MeasureFlightTimeBubbleStautsWord:quint8{
        st_BUBBLE_ENDMEASURE_TIME = 0x02,
        st_BUBBLE_MEASURERESPONSE_TIME = 0x09,
        st_BUBBLE_MEASURERESULT_TIME = 0x0A,
    };

    enum class BubbleDeviceId:quint8{
        LANEASENSOR = 0x01,
        LANEBSENSOR = 0x02,
        LANEABSENSOR = 0x03,
        WASTE1SENSOR = 0x04,
        LANEAWASTE1SENSOR = 0x05,
        LANEBWASTE1SENSOR = 0x06,
        LANEABWASTE1SENSOR = 0x07,
        WASTE2SENSOR = 0x08,
        LANEAWASTE2SENSOR = 0x09,
        LANEBWASTE2SENSOR = 0x0A,
        LANEABWASTE2SENSOR = 0x0B,
        WASTE12SENSOR = 0x0C,
        LANEAWASTE12SENSOR = 0x0D,
        LANEBWASTE12SENSOR = 0x0E,
        LANEABWASTE12SENSOR = 0x0F,
    };
    /**
     * @brief The FlowcellTemperatureControlWord enum flowcell温控控制字
     */
    enum class FlowcellTemperatureControlWord{
        CW_FCTC_HEATING_STOP=1,                             //停止加热
        CW_FCTC_HEATING_START=2,                            //开始加热
        CW_FCTC_COOLING_STOP=3,                             //停止降温
        CW_FCTC_COOLING_START=4,                            //开始降温
        CW_FCTC_HEATING_PID_SET=5,                          //加热过程PID参数设置
        CW_FCTC_COOLING_PID_SET=6,                          //降温过程PID参数设置
        CW_FCTC_TARGET_TEMPERATURE_SET=7,                   //设置加热/降温目标温度
        CW_FCTC_HEATING_TEMPERATURE_GET=8,                  //获得当前温度值
        CW_FCTC_SELF_CHECKING=9,                            //温控模块自检
        CW_FCTC_INIT=10,                                    //初始化
        CW_FCTC_STATE_GET=11,                               //获得温控模块状态
        CW_FCTC_WARNING_GET=12,                             //获得告警（出错）信息
    };

    /**
     * @brief The FlowcellTemperatureStatusWord enum Flowcell温控状态字
     */
    enum class FlowcellTemperatureStatusWord{
        st_FAN_RUN = 0x0100,                                //风扇运行
        st_COOLING = 0x0080,                                //正在降温
        st_HEATING = 0x0040,                                //正在加热
        st_FCTC_FAULT = 0x0020,                             //模块故障
        st_DEVICE_BUSY = 0x0010,                            //设备忙
        st_DEVICE_INIT = 0x0008,                            //设备初始化
        st_DEVICE_RUN = 0x0004,                             //设备正在运行
        st_DEVICE_OPEN = 0x0002,                            //设备打开
        st_DEVICE_INVALID = 0x0001,                         //设备无效
    };
    enum class XYStageDeviceId:quint8{
        XYSTAGEDEVICEID=0,
    };

    /**
     * @brief The XYStageControlWord enum XY运动平台控制字
     */
    enum class XYStageControlWord{
        CW_xySTAGE_STOP=1,                              //停止运行(急停)
        CW_xySTAGE_FINDING_XY_ZEROS=2,                  //平台XY轴寻零点（HOME点）
        CW_xySTAGE_FINDING_X_HOME=3,                    //平台X轴寻零点（HOME点）
        CW_xySTAGE_FINDING_Y_HOME=4,                    //平台Y轴寻零点（HOME点）
        CW_xySTAGE_FOLLOW_TO_SEQUENCING_P=5,            //随动至测序点
        CW_xySTAGE_FOLLOW_TO_HOME_P=6,                  //随动至HOME点
        CW_xySTAGE_P_TO_P_RELATIVE=7,                   //点到点相对移动
        CW_xySTAGE_CURRENT_LOCATION_GET=8,              //当前位置查询

        CW_xySTAGE_SPEED_SET=9,                         //速度设置
        CW_xySTAGE_ENCODER_GET=10,                      //读取编码器
        CW_xySTAGE_INIT=11,                             //XY平台初始化
        CW_xySTAGE_SELF_TEST=12,                        //平台自检
        CW_xySTAGE_STATE_GET=13,                        //获得XY平台状态
        CW_xySTAGE_FAULT_GET=14,                        //获得XY平台故障信息
        CW_xySTAGE_HAND_GET=15,                         //握手
    };
#ifndef SIMPLIFY
    /**
     * @brief The XYStageStatusWord enum XY运动平台状态字
     */
    enum class XYStageStatusWord{
        st_xySTAGE_y_ARRIVE = 0x0400,   //Y轴运行到位
        st_xySTAGE_x_ARRIVE = 0x0200,   //X轴运行到位
        st_xySTAGE_z_ZERO   = 0x0100,   //回到零点
        st_xySTAGE_y_RUN    = 0x0080,   //Y轴正在运行
        st_xySTAGE_x_RUN    = 0x0040,   //X轴正在运行
        st_DEVICE_FAULT     = 0x0020,   //设备故障
        st_DEVICE_BUSY      = 0x0010,   //设备忙
        st_DEVICE_INIT      = 0x0008,   //设备初始化
        st_DEVICE_RUN       = 0x0004,   //设备正在运行
        st_DEVICE_OPEN      = 0x0002,   //设备打开
        st_DEVICE_INVALID   = 0x0001,   //设备无效
    };
#else
    /**
     * @brief The XYStageStatusWord enum XY运动平台状态字
     */
    enum class XYStageStatusWord{
        st_DEVICE_INVALID   = 0x0001,   //操作错误
        st_DEVICE_SUCESS   = 0x0000,   //操作成功
    };
#endif

    /**
     * @brief The VoiceCoilMotorControlWord enum 音圈电机控制字
     */
    enum class VoiceCoilMotorControlWord{
        CW_VCM_STOP=1,                              //停止
        CW_VCM_FINDING_HOME=2,                      //寻零点（HOME点）
        CW_VCM_RELATIVE_MOTION=3,                   //相对运动
        CW_VCM_ABSOLUTE_MOTION=4,                   //绝对运动
        CW_VCM_GOHOME=5,                            //回到零点
        CW_VCM_MULTIPLE_POSITON_ACQUISITION=6,      //多次位置采集
        CW_VCM_CURRENT_LOCATION_GET=7,              //当前位置查询
        CW_VCM_INIT=8,                              //音圈电机初始化
        CW_VCM_SELF_TEST=9,                         //音圈电机自检
        CW_VCM_POWER_ON=10,                         //电机上电（使能）
        CW_VCM_POWER_OFF=11,                        //电机关电（失能）
        CW_VCM_STATE_GET=12,                        //获得音圈电机状态
        CW_VCM_FAULT_GET=13,                        //获得音圈电机故障信息
        CW_VCM_PARAMETERS_GET=14,                   //获得设置参数
    };

    /**
     * @brief The VoiceCoilMotorStatusWordFirst enum 音圈电机第一个状态字
     */
    enum class VoiceCoilMotorStatusWordFirst{
        st_VCM4_FAULT   = 0x8000,   //音圈电机4故障
        st_VCM4_RUN     = 0x4000,   //音圈电机4正在运行
        st_VCM4_ARRIVE  = 0x2000,   //音圈电机4运行到位
        st_VCM4_ZERO    = 0x1000,   //音圈电机4回到零点
        st_VCM3_FAULT   = 0x0800,   //音圈电机3故障
        st_VCM3_RUN     = 0x0400,   //音圈电机3正在运行
        st_VCM3_ARRIVE  = 0x0200,   //音圈电机3运行到位
        st_VCM3_ZERO    = 0x0100,   //音圈电机3回到零点
        st_VCM2_FAULT   = 0x0080,   //音圈电机2故障
        st_VCM2_RUN     = 0x0040,   //音圈电机2正在运行
        st_VCM2_ARRIVE  = 0x0020,   //音圈电机2运行到位
        st_VCM2_ZERO    = 0x0010,   //音圈电机2回到零点
        st_VCM1_FAULT   = 0x0008,   //音圈电机1故障
        st_VCM1_RUN     = 0x0004,   //音圈电机1正在运行
        st_VCM1_ARRIVE  = 0x0002,   //音圈电机1运行到位
        st_VCM1_ZERO    = 0x0001,   //音圈电机1回到零点
    };

    /**
     * @brief The VoiceCoilMotorStatusWordSecond enum 音圈电机第二个状态字
     */
    enum class VoiceCoilMotorStatusWordSecond{
        st_DEVICE_FAULT     = 0x0020,//模块故障
        st_DEVICE_BUSY      = 0x0010,//设备忙
        st_DEVICE_INIT      = 0x0008,//设备初始化
        st_DEVICE_RUN       = 0x0004,//设备正在运行
        st_DEVICE_OPEN      = 0x0002,//设备打开
        st_DEVICE_INVAID    = 0x0001,//设备无效
    };

    /**
     * @brief The PCUMoterControlWord enum 压力陶瓷超声波电机
     */
    enum class PCUMoterControlWord{
        CW_axisZ_PCUM_STOP=1,                                //停止运行
        CW_axisZ_PCUM_START=2,                               //开始运行
        CW_axisZ_PCUM_FINDING_ZEROS=3,                       //Z轴找寻零点
        CW_axisZ_PCUM_SPEED_SET=4,                           //速度设置
        CW_axisZ_PCUM_P_TO_P_RELATIVE=5,                     //点到点相对移动
        CW_axisZ_PCUM_P_TO_P_ABSOLUTE=6,                     //点到点绝对移动
        CW_axisZ_PCUM_CURRENT_LOCATION_GET=7,                //当前位置查询

        CW_axisZ_PCUM_INIT=8,                                //Z轴初始化
        CW_axisZ_PCUM_STATE_GET=9,                           //获得Z轴状态
        CW_axisZ_PCUM_FAULT_GET=10                           //获得Z轴故障信息
    };

    /**
     * @brief The PressureSensorDeviceID enum 液路压力传感器设备ID
     */
    enum class PressureSensorDeviceID:quint8
    {
        PRESSURESENSORPAIRA = 1,
        PRESSURESENSORPAIRB = 2,
    };

    /**
     * @brief The PressureSensorControlWord enum 液路压力传感器
     */
    enum class PressureSensorControlWord{
        CW_PV_GET=1,                               //获得压力值
    };

    /**
     * @brief The RFIDControlWord enum RFID控制字
     */
    enum class RFIDControlWord{
        CW_RFID_STOP=1,                                   //停止运行
        CW_RFID_START=2,                                  //开始运行
        CW_RFID_OPEN_ANTENNA=3,                           //开关天线
        CW_RFID_ACK_LABEL=4,                              //请求标签
        CW_RFID_CA_SET_LABEL=5,                           //防碰撞并选中标签
        CW_RFID_SLEEP_LABEL=6,                            //休眠标签
        CW_RFID_VALIDATE_KEY=7,                           //验证KEY
        CW_RFID_READ_DATA=8,                              //读某块数据
        CW_RFID_WRITE_DATA=9,                             //写某块数据
        CW_RFID_CHANGE_KEY=10,                            //修改KEY
        CW_RFID_READ_VERSION_ID=11,                       //读版本号
        CW_RFID_INIT=12,                                  //RFID模块初始化
        CW_RFID_STATE_GET=13,                             //获得RFID模块状态
        CW_RFID_FAULT_GET=14                              //获得RFID模块故障信息
    };

    /**
     * @brief The BufferAndWasteControlWord enum 液路自动化缓冲液/废液回收处理单元控制字
     */
    enum class BufferAndWasteControlWord{
        CW_raBWLRPU_INIT=1,                  //缓冲液/废液回收处理单元初始化
        CW_raBWLRPU_TO_TOP=2,               //吸管上升到上止点
        CW_raBWLRPU_TO_BOTTOM=3,           //吸管下降到下止点
        CW_raBWLRPU_GET_SENSOR_STATUS=4,   //获得缓冲液/废液回收处理单元传感器状态
        CW_raBWLRPU_GET_BWRPU_STATUS=5,    //获得缓冲液/废液回收处理单元状态
        //CW_raBWLRPU_STM_Init=6, //缓冲液/废液回收处理单元Z轴电机初始化(仅初始化电机寄存器)
    };

    /**
     * @brief The BufferAndWasterStatusWord enum MPCU主动上传液路自动化缓冲液/废液回收处理单元控制字
     */
    enum class BufferAndWasterStatusWord{
        st_raBWLRPU_NO_ERR=0,                          //没有错误
        st_raBWLRPU_RUNING=1,                          //正在运行
        st_raBWLRPU_AT_TOP=2,                          //在上止点
        st_raBWLRPU_AT_BOTTOM=3,                       //在下止点
        st_raBWLRPU_WASTE_BOX_EXISTS=4,                //存在废液盒
        st_raBWLRPU_BUFFER_BOX_EXISTS=5,               //存在缓冲液盒
        st_raBWLRPU_WASTE_FULL=6,                      //缓冲液满
        st_raBWLRPU_FAILED=7,                          //故障( 详细故障参看具体错误代码)
    };

    /**
     * @brief The ReagentAssembleProcessingControlWord enum 液路自动化试剂装配处理单元
     */
    enum class ReagentAssembleProcessingControlWord{
        CW_raRAPU_INIT=1,                               //试剂装配处理单元初始化

        CW_raRAPU_Z_TRAY_FROM_DOWN_TO_SEQUECING=2,      //试剂托盘从DOWN点到SEQUECING点
        CW_raRAPU_Z_TRAY_FROM_DOWN_TO_UP=3,             //试剂托盘从DOWN 到上止点(up)
        CW_raRAPU_Z_TRAY_FROM_UP_TO_SEQUENCING=4,       //试剂托盘从UP点到SEQUENCING点
        CW_raRAPU_Z_TRAY_FROM_SEQUECING_TO_DOWN=5,      //试剂托盘从SEQUECING 到下止点(DOWN)
        CW_raRAPU_Z_TRAY_FROM_SEQUECING_TO_UP=6,        //试剂托盘从SEQUECING 到上止点(up)
        CW_raRAPU_Z_TRAY_FROM_UP_TO_DOWN=7,             //试剂托盘从UP点到下止点(dowm)


        CW_raRAPU_Y_SIPPER_FROM_HOME_TO_BACK=8,         //试剂吸管Y从HOME点（试剂孔）到BACK点(清洗孔)
        CW_raRAPU_Y_SIPPER_FROM_HOME_TO_FORWARD=9,      //试剂吸管Y从HOME点（试剂孔）到FORWARD 前止点（原点）
        CW_raRAPU_Y_SIPPER_FROM_BACK_TO_FORWARD=10,     //试剂吸管Y从BACK（清洗孔）点到FORWARD前止点（原点）     0x0A
        CW_raRAPU_Y_SIPPER_FROM_BACK_TO_HOME=11,        //试剂吸管Y从BACK（清洗孔）点到HOME点（清洗孔）0x0B
        CW_raRAPU_Y_SIPPER_FROM_FORWARD_TO_HOME=12,     //试剂吸管Y从FORWAR前止点（原点）到HOME点（试剂孔）    0x0C
        CW_raRAPU_Y_SIPPER_FROM_FORWARD_TO_BACK=13,     //试剂吸管Y从FORWARD前止点（原点）到BACK点（清洗孔）   0x0D


        CW_raRAPU_Z_TRAY_STOP=14,                       //Z轴急停      0x0E
        CW_raRAPU_Y_SIPPER_STOP=15,                     //Y轴急停      0x0F
        CW_raRAPU_GET_SENSOR_STATUS=16,                 //获得试剂装配处理单元传感器状态信息
        CW_raRAPU_GET_RAPU_STATUS=17,                   //获得试剂装配处理单元状态信息
    };

    /**
     * @brief The ReagentAssembleProcessingStatusWord enum MPCU主动上传的试剂装配处理单元状态字
     */
    enum class ReagentAssembleProcessingStatusWord{
        st_raRAPU_NO_ERR=0,                          //没有错误
        st_raRAPU_RUNING=1,                          //正在运行
        st_raRAPU_TRAY_AT_UP=2,                      //试剂托盘在up点
        st_raRAPU_TRAY_AT_DOWN=3,                    //试剂托盘在DOWN点
        st_raRAPU_TRAY_AT_PRESENT=4,                 //试剂托盘在PRESENT点
        st_raRAPU_TRAY_AT_BACK=5,                    //试剂托盘在BACK点
        st_raRAPU_TRAY_AT_SEQUENCING=6,              //试剂托盘在SEQUENCING点
        st_raRAPU_SIPPER_AT_HOME=7,                  //试剂吸管在HOME点
        st_raRAPU_SIPPER_AT_FORWARD=8,               //试剂吸管在FORWARD点
        st_raRAPU_SIPPER_AT_CLEANING=9,              //试剂吸管在清洗位
        st_raRAPU_REAGENT_EXISTS=10,                 //存在试剂盒
        st_raRAPU_FAILED=11,                         //故障(详细故障参看具体错误代码)
    };

    /**
     * @brief The ReagentDistributionProcessingControlWord enum 液路自动化之试剂分配处理单元
     */
    enum class ReagentDistributionProcessingControlWord{
        CW_raRDPU_INIT=1,                               //试剂分配处理单元初始化（）

        CW_raRDPU_OPEN_THREE_WAY_VALVE=2,               //打开三通阀
        CW_raRDPU_CLOSE_THREE_WAY_VALVE=3,              //关闭三通阀
        CW_raRDPU_OPEN_DEGASSER=4,                      //打开脱气装置
        CW_raRDPU_CLOSE_DEGASSER=5,                     //关闭脱气装置
        CW_raRDPU_BUBBLE_DETECTION=6,                   //气泡检测
        CW_raRDPU_GET_PRESSURE=7,                       //读取液路压力值
        CW_raRDPU_GET_FLOW_RATE=8,                      //读取液路流速值
        CW_raRDPU_GET_SENSOR_STATUS=9,
        CW_raRDPU_GET_RAPU_STATUS=9,                    //获得试剂分配处理单元状态信息
    };

    /**
     * @brief The CaseTemperatureProcssingControlWord enum 机箱温度控制字
     */
    enum class CaseTemperatureProcssingControlWord{
        CW_tempMU_FanClose=1,                     //关闭风扇
        CW_tempMU_FanOpen=2,                      //打开风扇
        CW_tempMU_FanRunFlag_Get=3,               //获得风扇运行状态（==1,运行；==0,停止）
        CW_tempMU_FanFault_Get=4,                 //获得风扇故障位
        CW_tempMU_Thermocouple_Get=5,             //获取热电偶温度值
        CW_tempMU_ThermocoupleReg_Get=6,          //获取热电偶内部寄存器值
        CW_tempMU_ThermocoupleFault_Get=7,        //获得热电偶故障位
        CW_tempMU_TemperatureBoard_Get=8,         //获得板载温度
        CW_tempMU_Unit_Init=9,                    //初始化温度管理单元
    };

    /**
     * @brief The DeviceStatusWord enum 设备状态字
     */
    enum class DeviceStatusWord{
        DE_INVALID=0,         //无此设备
        DE_OPEND=1,           //设备已打开
        DE_COLSED=2,          //设备已关闭
        DE_RUNING=3,          //设备正在运行
        DE_COMPLETE=4,        //设备运行完成
        DE_INI_OK=5,          //初始化完成
        DE_BUSY=6,            //设备忙
        DE_READY=7,           //设备就绪
    };

    /**
     * @brief The DeviceErrorWord enum 设备错误信息
     */
    enum class DeviceErrorWord{
        DE_ERR_NONE=0x00,               //设备没有错误
        DE_ERR_TIMEOUT,                 //运行超时
        DE_ERR_COM,                     //设备通讯出错
        DE_ERR_RUN,                     //运行出错（没有动作或运行不到位）
        DE_ERR_PARA,                    //参数错误
        DE_ERR_INI,                     //初始化错误
        DE_ERR_FAULT,                   //设备故障
    };
}

enum class TestEnum{x, b, c};
Q_DECLARE_METATYPE(TestEnum)
#endif // ENUMS_H
