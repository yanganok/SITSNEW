#include "globalSet.h"
#include "Tools/imagebase.h"
#include "Tools/grayimage.h"
#include "responses/audio_command_response.h"
#include "responses/bubblecalibrate_command_response.h"
#include "responses/bubblegetcount_command_response.h"
#include "responses/bubblewatchrecord_command_response.h"
#include "responses/bubblewatchsensors_command_response.h"
#include "responses/cameraenablezsettling_command_response.h"
#include "responses/camera_command_response.h"
#include "Responses/camerapenalty_command_response.h"
#include "Responses/cameraevent_command_response.h"
#include "Responses/camerareadleddata_command_response.h"
#include "Responses/camerareadledgain_command_response.h"
#include "Responses/camerasetaf_command_response.h"
#include "Responses/camerasnap_command_response.h"
#include "Responses/camerasnapfreeall_command_response.h"
#include "Responses/camerasnapfree_command_response.h"
#include "Responses/camerastoreledgains_command_response.h"
#include "Responses/fangetppm_command_response.h"
#include "Responses/fanonoff_command_response.h"
#include "Responses/fanthermalcontrol_command_response.h"
#include "Responses/flowcelldoorclose_command_response.h"
#include "Responses/flowcelldoorgetstate_command_response.h"
#include "Responses/flowcelldooropen_command_response.h"
#include "Responses/flowcelldoorsetsealdistance_command_response.h"
#include "Responses/fluidicsautomationnull_command_response.h"
#include "Responses/fluidicsautomationdo_command_response.h"
#include "Responses/fluidicsautomationgetpos_command_response.h"
#include "Responses/humidityread_command_response.h"
#include "Responses/loggetlist_command_response.h"
#include "Responses/logrecord_command_response.h"
#include "Responses/logreplay_command_response.h"
#include "Responses/miscfwidstr_command_response.h"
#include "Responses/miscfwstage_command_response.h"
#include "Responses/motionmove_command_response.h"
#include "Responses/motionreadencoder_command_response.h"
#include "Responses/motionnotify_command_response.h"
#include "Responses/motionservohistory_command_response.h"
#include "Responses/motionservorec_command_response.h"
#include "Responses/pressuresensorread_command_response.h"
#include "Responses/pumpdata_command_response.h"
#include "Responses/pumpwrite_command_response.h"
#include "Responses/rfidtag_command_response.h"
#include "Responses/rfidtagget_command_response.h"
#include "Responses/rfidtaggetstatus_command_response.h"
#include "Responses/rfidtagreset_command_response.h"
#include "Responses/rfidtagset_command_response.h"
#include "Responses/rfidtagvalidation_command_response.h"
#include "Responses/sampleheatercalculatepoint_command_response.h"
#include "Responses/sampleheatercalculatepoints_command_response.h"
#include "Responses/sampleheatercalculatereset_command_response.h"
#include "Responses/sampleheaterconnected_command_response.h"
#include "Responses/sampleheaterdisable_command_response.h"
#include "Responses/sampleheaterenable_command_response.h"
#include "Responses/sampleheatertemperature_command_response.h"
#include "Responses/sampleheatertargetget_command_response.h"
#include "Responses/sampleheatertargetset_command_response.h"
#include "Responses/sensorpositionrecord_command_response.h"
#include "Responses/sensorposition_command_response.h"
#include "Responses/sensornotify_command_response.h"
#include "Responses/sensoroverride_command_response.h"
#include "Responses/sensorread_command_response.h"
#include "Responses/settinsvoid_command_response.h"
#include "Responses/settingsget_command_response.h"
#include "Responses/settingsgetkeynames_command_response.h"
#include "Responses/settingsvoid_command_response.h"
#include "Responses/shutdownis_command_response.h"
#include "Responses/systemled_command_response.h"
#include "Responses/timegetmsec_command_response.h"
#include "Responses/timesetclock_command_response.h"
#include "Responses/valvedata_command_response.h"
#include "Responses/valvewrite_command_response.h"
#include "Responses/xyenablerangecheck_command_response.h"
#include "Responses/xygetposition_command_response.h"
#include "Responses/xyhealthy_command_response.h"
#include "Responses/xymoveto_command_response.h"
#include "Responses/xymovetoship_command_response.h"
#include "Responses/xyoffset_command_response.h"
#include "Responses/xyreinitialize_command_response.h"
#include "Responses/xysetminmovemsec_command_response.h"
#include "Responses/xysetsettlemsec_command_response.h"
#include "Responses/xystatus_command_response.h"
#include "Responses/xytargetset_command_response.h"
#include "Responses/xytargetgo_command_response.h"
#include "Responses/zstagegetheightresult_command_response.h"
#include "Responses/zstagegetheight_command_response.h"
#include "Responses/zstageinitialize_command_response.h"
#include "Responses/zstageisready_command_response.h"
#include "Responses/zstagesetheight_command_response.h"
#include "Responses/zstagewatchheight_command_response.h"
#include "Responses/cancel_command_response.h"
#include "Responses/getinterfacesignature_command_response.h"
#include "Responses/pumpabsorb_command_response.h"
#include "Responses/pumpdispense_command_response.h"
#include "Responses/pumpinit_command_response.h"
#include "Responses/xyinit_command_response.h"
#include "Responses/xymoveto_command_response.h"
#include "Responses/xyemergencystop_commmand_response.h"
#include "Responses/xyhand_command_response.h"
//#include "Responses/valvegetposition_command_response.h"

const QString GlobalPath::localFilePath = QDir::currentPath();
const QString IniFile::IniFileName = GlobalPath::localFilePath + "/config/system.ini";
//const int Sensor_Module::pressureMaintainingThreshold = 18;
//const int Sensor_Module::pressureMaintainingInspectionCycleLimit = 15;

QReadWriteLock Image_Module::ImageLocker::_multiImageWithSameNameLock;
void registerType()
{
    qRegisterMetaType<Response>("Response");
    qRegisterMetaType<std::shared_ptr<Response>>("std::shared_ptr<Response>");
    qRegisterMetaType<Audio_Command_Response>("Audio_Command_Response");
    qRegisterMetaType<BubbleCalibrate_Command_Response>("BubbleCalibrate_Command_Response");
    qRegisterMetaType<BubbleGetCount_Command_Response>("BubbleGetCount_Command_Response");
    qRegisterMetaType<BubbleWatchRecord_Command_Response>("BubbleWatchRecord_Command_Response");
    qRegisterMetaType<BubbleWatchSensors_Command_Response>("BubbleWatchSensors_Command_Response");
    qRegisterMetaType<CameraEnableZSettling_Command_Response>("CameraEnableZSettling_Command_Response");
    qRegisterMetaType<Camera_Command_Response>("Camera_Command_Response");
    qRegisterMetaType<CameraPenalty_Command_Response>("CameraPenalty_Command_Response");
    qRegisterMetaType<CameraEvent_Command_Response>("CameraEvent_Command_Response");
    qRegisterMetaType<CameraReadLEDData_Command_Response>("CameraReadLEDData_Command_Response");
    qRegisterMetaType<CameraReadLEDGain_Command_Response>("CameraReadLEDGain_Command_Response");
    qRegisterMetaType<CameraSetAF_Command_Response>("CameraSetAF_Command_Response");
    qRegisterMetaType<CameraSnapFreeAll_Command_Response>("CameraSnapFreeAll_Command_Response");
    qRegisterMetaType<CameraSnapFree_Command_Response>("CameraSnapFree_Command_Response");
    qRegisterMetaType<CameraStoreLEDGains_Command_Response>("CameraStoreLEDGains_Command_Response");
    qRegisterMetaType<FanGetPPM_Command_Response>("FanGetPPM_Command_Response");
    qRegisterMetaType<FanOnOff_Command_Response>("FanOnOff_Command_Response");
    qRegisterMetaType<FanThermalControl_Command_Response>("FanThermalControl_Command_Response");
    qRegisterMetaType<FlowcellDoorClose_Command_Response>("FlowcellDoorClose_Command_Response");
    qRegisterMetaType<FlowcellDoorGetState_Command_Response>("FlowcellDoorGetState_Command_Response");
    qRegisterMetaType<FlowcellDoorOpen_Command_Response>("FlowcellDoorOpen_Command_Response");
    qRegisterMetaType<FlowcellDoorSetSealDistance_Command_Response>("FlowcellDoorSetSealDistance_Command_Response");
    qRegisterMetaType<FluidicsAutomationNull_Command_Response>("FluidicsAutomationNull_Command_Response");
    qRegisterMetaType<FluidicsAutomationDo_Command_Response>("FluidicsAutomationDo_Command_Response");
    qRegisterMetaType<FluidicsAutomationGetPos_Command_Response>("FluidicsAutomationGetPos_Command_Response");
    qRegisterMetaType<HumidityRead_Command_Response>("HumidityRead_Command_Response");
    qRegisterMetaType<LogGetList_Command_Response>("LogGetList_Command_Response");
    qRegisterMetaType<LogRecord_Command_Response>("LogRecord_Command_Response");
    qRegisterMetaType<LogReplay_Command_Response>("LogReplay_Command_Response");
    qRegisterMetaType<MiscFWIdStr_Command_Response>("MiscFWIdStr_Command_Response");
    qRegisterMetaType<MiscFWStage_Command_Response>("MiscFWStage_Command_Response");
    qRegisterMetaType<MotionMove_Command_Response>("MotionMove_Command_Response");
    qRegisterMetaType<MotionReadEncoder_Command_Response>("MotionReadEncoder_Command_Response");
    qRegisterMetaType<MotionNotify_Command_Response>("MotionNotify_Command_Response");
    qRegisterMetaType<MotionServoHistory_Command_Response>("MotionServoHistory_Command_Response");
    qRegisterMetaType<MotionServoRec_Command_Response>("MotionServoRec_Command_Response");
    qRegisterMetaType<PressureSensorRead_Command_Response>("PressureSensorRead_Command_Response");
    qRegisterMetaType<PumpData_Command_Response>("PumpData_Command_Response");
    qRegisterMetaType<PumpWrite_Command_Response>("PumpWrite_Command_Response");
    qRegisterMetaType<RFIDTag_Command_Response>("RFIDTag_Command_Response");
    qRegisterMetaType<RFIDTagGet_Command_Response>("RFIDTagGet_Command_Response");
    qRegisterMetaType<RFIDTagGetStatus_Command_Response>("RFIDTagGetStatus_Command_Response");
    qRegisterMetaType<RFIDTagReset_Command_Response>("RFIDTagReset_Command_Response");
    qRegisterMetaType<RFIDTagSet_Command_Response>("RFIDTagSet_Command_Response");
    qRegisterMetaType<RFIDTagValidation_Command_Response>("RFIDTagValidation_Command_Response");
    qRegisterMetaType<SampleHeaterCalculatePoint_Command_Response>("SampleHeaterCalculatePoint_Command_Response");
    qRegisterMetaType<SampleHeaterCalculatePoints_Command_Response>("SampleHeaterCalculatePoints_Command_Response");
    qRegisterMetaType<SampleHeaterCalculateReset_Command_Response>("SampleHeaterCalculateReset_Command_Response");
    qRegisterMetaType<SampleHeaterConnected_Command_Response>("SampleHeaterConnected_Command_Response");
    qRegisterMetaType<SampleHeaterDisable_Command_Response>("SampleHeaterDisable_Command_Response");
    qRegisterMetaType<SampleHeaterEnable_Command_Response>("SampleHeaterEnable_Command_Response");
    qRegisterMetaType<SampleHeaterTemperature_Command_Response>("SampleHeaterTemperature_Command_Response");
    qRegisterMetaType<SampleHeaterTargetGet_Command_Response>("SampleHeaterTargetGet_Command_Response");
    qRegisterMetaType<SampleHeaterTargetSet_Command_Response>("SampleHeaterTargetSet_Command_Response");
    qRegisterMetaType<SensorPositionRecord_Command_Response>("SensorPositionRecord_Command_Response");
    qRegisterMetaType<SensorPosition_Command_Response>("SensorPosition_Command_Response");
    qRegisterMetaType<SensorNotify_Command_Response>("SensorNotify_Command_Response");
    qRegisterMetaType<SensorOverride_Command_Response>("SensorOverride_Command_Response");
    qRegisterMetaType<SensorRead_Command_Response>("SensorRead_Command_Response");
    qRegisterMetaType<SettinsVoid_Command_Response>("SettinsVoid_Command_Response");
    qRegisterMetaType<SettingsGet_Command_Response>("SettingsGet_Command_Response");
    qRegisterMetaType<SettingsGetKeyNames_Command_Response>("SettingsGetKeyNames_Command_Response");
    qRegisterMetaType<SettingsVoid_Command_Response>("SettingsVoid_Command_Response");
    qRegisterMetaType<ShutDownIs_Command_Response>("ShutDownIs_Command_Response");
    qRegisterMetaType<SystemLED_Command_Response>("SystemLED_Command_Response");
    qRegisterMetaType<TimeGetMSEC_Command_Response>("TimeGetMSEC_Command_Response");
    qRegisterMetaType<TimeSetClock_Command_Response>("TimeSetClock_Command_Response");
    qRegisterMetaType<ValveData_Command_Response>("ValveData_Command_Response");
    qRegisterMetaType<ValveWrite_Command_Response>("ValveWrite_Command_Response");
    qRegisterMetaType<XYEnableRangeCheck_Command_Response>("XYEnableRangeCheck_Command_Response");
    qRegisterMetaType<XYGetPosition_Command_Response>("XYGetPosition_Command_Response");
    qRegisterMetaType<XYHealthy_Command_Response>("XYHealthy_Command_Response");
    qRegisterMetaType<XYMoveTo_Command_Response>("XYMoveTo_Command_Response");
    qRegisterMetaType<XYMoveToShip_Command_Response>("XYMoveToShip_Command_Response");
    qRegisterMetaType<XYOffset_Command_Response>("XYOffset_Command_Response");
    qRegisterMetaType<XYReinitialize_Command_Response>("XYReinitialize_Command_Response");
    qRegisterMetaType<XYSetMinMoveMsec_Command_Response>("XYSetMinMoveMsec_Command_Response");
    qRegisterMetaType<XYSetSettleMsec_Command_Response>("XYSetSettleMsec_Command_Response");
    qRegisterMetaType<XYStatus_Command_Response>("XYStatus_Command_Response");
    qRegisterMetaType<XYTargetSet_Command_Response>("XYTargetSet_Command_Response");
    qRegisterMetaType<XYTargetGo_Command_Response>("XYTargetGo_Command_Response");
    qRegisterMetaType<ZStageGetHeightResult_Command_Response>("ZStageGetHeightResult_Command_Response");
    qRegisterMetaType<ZStageGetHeight_Command_Response>("ZStageGetHeight_Command_Response");
    qRegisterMetaType<ZStageInitialize_Command_Response>("ZStageInitialize_Command_Response");
    qRegisterMetaType<ZStageIsReady_Command_Response>("ZStageIsReady_Command_Response");
    qRegisterMetaType<ZStageSetHeight_Command_Response>("ZStageSetHeight_Command_Response");
    qRegisterMetaType<ZStageWatchHeight_Command_Response>("ZStageWatchHeight_Command_Response");
    qRegisterMetaType<Cancel_Command_Response>("Cancel_Command_Response");
    qRegisterMetaType<GetInterfaceSignature_Command_Response>("GetInterfaceSignature_Command_Response");
    qRegisterMetaType<PumpAbsorb_Command_Response>("PumpAbsorb_Command_Response");
    qRegisterMetaType<PumpDispense_Command_Response>("PumpDispense_Command_Response");
    qRegisterMetaType<PumpInit_Command_Response>("PumpInit_Command_Response");
    qRegisterMetaType<XYInit_Command_Response>("XYInit_Command_Response");
    qRegisterMetaType<XYEmergencyStop_Commmand_Response>("XYEmergencyStop_Commmand_Response");
    qRegisterMetaType<XYMoveTo_Command_Response>("XYMoveTo_Command_Response");
    qRegisterMetaType<XYHand_Command_Response>("XYHand_Command_Response");
//    qRegisterMetaType<ValveGetPosition_Command_Response>("ValveGetPosition_Command_Response");

    qRegisterMetaType<TestEnum>("TestEnum");
}


void Image_Module::Header::write(QDataStream& writer)
{
    this->_formatID1 = 73;
    this->_formatID2 = 73;
    this->_tiffID = 42;
    this->_offsetToIFD = (quint32)sizeof(Image_Module::Header);
    writer << this->_formatID1 << this->_formatID2 << this->_tiffID << this->_offsetToIFD;
}

void Image_Module::Header::write(QByteArray &writer)
{
    this->_formatID1 = 73;
    this->_formatID2 = 73;
    this->_tiffID = 42;
    this->_offsetToIFD = (quint32)sizeof(Image_Module::Header);
    writer.append(reinterpret_cast<char *>(&_formatID1), sizeof(_formatID1));
    writer.append(reinterpret_cast<char *>(&_formatID2), sizeof(_formatID2));
    writer.append(reinterpret_cast<char *>(&_tiffID), sizeof(_tiffID));
    writer.append(reinterpret_cast<char *>(&_offsetToIFD), sizeof(_offsetToIFD));
}

Image_Module::IFD::IFD(Global::TAG tag, Global::Type type, quint32 count, quint32 value)
    :_tag(tag), _type(type), _count(count), _value(value)
{

}

void Image_Module::IFD::write(QDataStream &writer)
{
    writer << _tag << _type << _count << _value;
}

void Image_Module::IFD::write(QByteArray &writer)
{
    quint16 tag = static_cast<quint16>(_tag);
    quint16 type = static_cast<quint16>(_type);
    quint32 count = static_cast<quint32>(_count);
    writer.append(reinterpret_cast<char *>(&tag), sizeof(tag));
    writer.append(reinterpret_cast<char *>(&type), sizeof(type));
    writer.append(reinterpret_cast<char*>(&count), sizeof(count));
    writer.append(reinterpret_cast<char *>(&_value), sizeof(_value));
}

void Image_Module::SaveChunkAsTiffFile(quint16 *imagePtr, int imageWidth, int linesToWrite, const QString& fileName, Image_Module::OverwriteHandling overwriteHandling)
{
    QFile file(fileName);
    if(file.exists()){
        switch (overwriteHandling) {
        case Image_Module::OverwriteHandling::THROWEXCEPTION:
            throw ApplicationException(QString("Cannot save image to file %1 because file already exists.").arg(fileName));
            break;
        case Image_Module::OverwriteHandling::BACKUPCURRENTFILEFIRST:
            BackupCurrentFile(fileName);
            break;
        case Image_Module::OverwriteHandling::RENAMENEW:
            GetNewFileName(fileName);
            break;
        }
    }
    QFileInfo info;
    info.setFile(file);
    QString folder = info.absolutePath();
    if(folder == "")
    {
        throw ApplicationException(QString("Please provide a full path rather than the following:%1").arg(fileName));
    }
    QDir dir;
    dir.setPath(folder);
    if(!dir.exists())
    {
        dir.mkdir(folder);
    }
    try{
        QVector<IFD> directoryEntries{
            IFD(Global::TAG::NEWSUBFILETYPE, Global::Type::LONG, 1u, 0u),
            IFD(Global::TAG::IMAGEWIDTH, Global::Type::LONG, 1u, imageWidth),
            IFD(Global::TAG::IMAGELENGTH, Global::Type::LONG, 1u, linesToWrite),
            IFD(Global::TAG::BITSPERSAMPLE, Global::Type::SHORT, 1u, 16u),
            IFD(Global::TAG::COMPRESSION, Global::Type::SHORT, 1u, 1u),
            IFD(Global::TAG::PHOTOMETRICINTERPRETATION, Global::Type::SHORT, 1u, 1u),
            IFD(Global::TAG::STRIPOFFSETS, Global::Type::LONG, 1u, 0u),
            IFD(Global::TAG::SAMPLESPERPIXEL, Global::Type::SHORT, 1u, 1u),
            IFD(Global::TAG::ROWSPERSTRIP, Global::Type::LONG, 1u, linesToWrite),
            IFD(Global::TAG::STRIPBYTECOUNTS, Global::Type::LONG, 1u, (linesToWrite * imageWidth * 2))
        };
        int offsetToImageData = sizeof(Header) + directoryEntries.size() * sizeof(IFD) + 4;
        QFile file(fileName);
        file.resize(512);
        if(file.open(QIODevice::ReadWrite))
        {
            QByteArray writer;
            Header header;
            header.write(writer);
            quint16 dicSize = static_cast<quint16>(directoryEntries.size());
            writer.append((char *)&dicSize, 2);
            for (int i = 0; i < directoryEntries.size(); ++i)
            {
                IFD ifd = directoryEntries[i];
                if (ifd._tag == Global::TAG::STRIPOFFSETS)
                {
                    ifd._value = offsetToImageData;
                }
                ifd.write(writer);
            }
            quint32 zero = 0;
            writer.append(reinterpret_cast<char*>(&zero), sizeof(zero));
            quint8 *p = file.map(0, 512);
            if(p != nullptr)
            {
                memcpy(p, writer.data(), 512);
                file.unmap(p);
                p = nullptr;
            }
            qint64 imageSize = imageWidth * linesToWrite * 2;
            file.resize(imageSize + offsetToImageData);
            quint32 begin = 0;
            while(imageSize > 0)
            {
                if (!file.isOpen())
                    file.open(QIODevice::ReadWrite);
                p = file.map(offsetToImageData, imageSize > Image_Module::MapBufferSize ? Image_Module::MapBufferSize:imageSize);
                memcpy(p, (char *)imagePtr + begin, imageSize > Image_Module::MapBufferSize ? Image_Module::MapBufferSize:imageSize);
                imageSize -= Image_Module::MapBufferSize;
                offsetToImageData += Image_Module::MapBufferSize;
                begin += Image_Module::MapBufferSize;
                file.unmap(p);
                if (file.isOpen())
                    file.close();
                p = nullptr;
            }
            file.close();
        }
    }
    catch(QException& ex)
    {

    }
}

void Image_Module::BackupCurrentFile(const QString& currentPath)
{
    QFileInfo fileInfo(currentPath);
    QString folder = fileInfo.absolutePath();
    QString fileBase = fileInfo.baseName();
    QString suffix = fileInfo.suffix();
    for (int i = 0; i < 1000; ++i)
    {
        QString newFileName = QString("%1/%2%3%4.%5").arg(folder, fileBase, "old", QString::number(i), suffix);
        QFileInfo newFileInfo(newFileName);
        if (!newFileInfo.exists())
        {
            QFile(currentPath).rename(newFileName);
            break;
        }
    }
}

void Image_Module::GetNewFileName(const QString &fileName)
{

}

void Image_Module::SaveAsTiffFile(Image_Module::ImageStruct imageStruct, const QString &fileName, Image_Module::OverwriteHandling overwriteHandling)
{
    std::shared_ptr<quint16> pData = imageStruct.data;
    SaveChunkAsTiffFile(pData.get(), imageStruct.width, imageStruct.height, fileName, overwriteHandling);
}

void Image_Module::SaveAsTiffFile(ImageBase *image, const QString &fileName, Image_Module::OverwriteHandling overwriteHandling)
{
    ImageLocker::_multiImageWithSameNameLock.lockForWrite();
    SaveAsTiffFile(image->imageStruct(), fileName, overwriteHandling);
    ImageLocker::_multiImageWithSameNameLock.unlock();
}

void Image_Module::LoadFromTiffFile(ImageBase *imageBase, const QString &fileName)
{
    QFile file(fileName);
    QByteArray cacheBuffer;
    if(file.open(QIODevice::ReadWrite))
    {
        int fileSize = file.size();
        int begin = 0;
        int offset = 4;

        while(fileSize > 0)
        {
            if (!file.isOpen())
            {
                file.open(QIODevice::ReadWrite);
            }
            quint8 *buffer = file.map(begin, fileSize > Image_Module::MapBufferSize ? Image_Module::MapBufferSize : fileSize);
            cacheBuffer.append((char *)buffer, fileSize > Image_Module::MapBufferSize ? Image_Module::MapBufferSize : fileSize);
            //DebugOut(cacheBuffer.size());
            file.unmap(buffer);
            //buffer = nullptr;
            if (file.isOpen())
                file.close();
            if(begin == 0)
            {
                if(cacheBuffer.at(0) != cacheBuffer.at(1))
                {
                    throw ApplicationException("Invalid tiff");
                    return;
                }
                if(cacheBuffer.at(0) != 73)
                {
                    throw ApplicationException("Not stored in Intel format");
                    return;
                }
                if(cacheBuffer.at(2) != 42)
                {
                    throw ApplicationException("Invalid tiff");
                    return;
                }
                int vali;
                memcpy(&vali, cacheBuffer.data() + offset, sizeof(vali));
                offset += sizeof(vali);
            }
            begin += Image_Module::MapBufferSize;
            fileSize -= Image_Module::MapBufferSize;
            if(file.isOpen())
                file.close();
        }
        int width = 0;
        int height = 0;
        int numStrips = 0;
        int rowsPerStrip = 0;
        int stripOffset = 0;
        int bytePerStrip = 0;
        int samplesPerPixel = 1;
        qint16 numFields;
        memcpy(&numFields, cacheBuffer.data() + offset, sizeof(numFields));
        offset += sizeof(numFields);
        int bpp = 0;
        for(int i = 0; i < numFields; ++i)
        {
            qint16 tag;
            int count;
            int value;
            memcpy(&tag, cacheBuffer.data() + offset, sizeof(tag));
            offset += sizeof(tag);
            qint16 vals;
            memcpy(&vals, cacheBuffer.data() + offset, sizeof(vals));
            offset += sizeof(vals);
            memcpy(&count, cacheBuffer.data() + offset, sizeof(count));
            offset += sizeof(count);
            if(vals == 3)
            {
                memcpy(&vals, cacheBuffer.data() + offset, sizeof(vals));
                offset += sizeof(vals);
                value = vals;
                offset += sizeof(vals);
            }
            else
            {
                memcpy(&value, cacheBuffer.data() + offset, sizeof(value));
                offset += sizeof(value);
            }
            switch (tag) {
            case 254:
                if(value != 0){
                    throw ApplicationException("Invalid tiff");
                }
                break;
            case 255:
                break;
            case 256:
                width = value;
                break;
            case 257:
                height = value;
                break;
            case 258:
                bpp = value;
                break;
            case 259:
                if(value != 1)
                {
                    throw ApplicationException("Invalid compression");
                }
                break;
            case 273:
                stripOffset = value;
                break;
            case 277:
                samplesPerPixel = value;
                break;
            case 278:
                rowsPerStrip = value;
                break;
            case 279:
                bytePerStrip = value;
                numStrips = count;
                break;
            default:
                break;
            }
        }
        if(bpp != 16)
            throw ApplicationException("Invalid tiff");
        if(numStrips == 0)
            throw ApplicationException("Invalid tiff");
        if(width == 0 || height == 0)
            throw ApplicationException("Invalid tiff");
//        imageBase->locker().lockForWrite();
        imageBase->resizeImage(width, height);
        ImageStruct imageStruct = imageBase->imageStruct();
        if(imageStruct.data.get() == nullptr || imageStruct.height != height || imageStruct.width != width)
            throw ApplicationException(QString("Derived image class %1 can not handle loading TIFF images from file %2;buffer ar not correctly allocated").arg(typeid(imageBase).name()).arg(fileName));
        for(int i = 0; i < numStrips; ++i)
        {
            int pos;
            int size;
            offset = stripOffset + i * 4;
            if(numStrips > 1)
            {
                memcpy(&pos, cacheBuffer.data() + offset, sizeof(pos));
                offset = bytePerStrip + i * 4;
                memcpy(&size, cacheBuffer.data() + offset, sizeof(size));
            }
            else
            {
                size = bytePerStrip;
                pos = stripOffset;
            }
            offset = pos;
            quint16 *from = reinterpret_cast<quint16 *>(cacheBuffer.data() + offset);
            quint16 *testptr = imageStruct.data.get();
            quint16 *to = reinterpret_cast<quint16 *>(imageStruct.data.get() + i * width * rowsPerStrip);
            size /= 2;
            size /= samplesPerPixel;
            for(int j = 0; j < size; ++j)
            {
                *to = *from;
                to++;
                from += samplesPerPixel;
            }
        }
//        imageBase->locker().unlock();
        emit imageBase->evImageChanged(imageBase, ImageChangedEventArgs());
    }
}

void Image_Module::LoadCompressedImage(QString filePath, GrayImage *image)
{
    QFileInfo info(filePath);
    QString filename = info.baseName() + ".jpg";
    QString path = info.absoluteDir().absolutePath() + filename;
    QFile file(path);
    if(file.exists(path))
    {
        QImage imageSource(path);
        try
        {
            int width = imageSource.width();
            int height = imageSource.height();
            int stride = imageSource.bytesPerLine();
            quint8 *scan0 = imageSource.bits();
            image->resizeImage(width, height);
            quint16 *data = image->data().get();
            int imgWidth = image->width();
            int imgHeight = image->height();
            int offset = stride - width * 3;
            quint8 *p = scan0;
            for(int y = 0; y < height; ++y)
            {
                for(int x = 0; x < width; ++x)
                {
                    *(data + y * width + x) = static_cast<quint16>(10 * *(p++));
                    ++p;
                    ++p;
                }
                p += offset;
            }
            data = nullptr;
            bool *validRow = image->validRow().data();
            for(int i = 0; i < image->height(); ++i)
            {
                *(validRow + i) = true;
            }
            validRow = nullptr;
            emit image->evImageChanged(image, ImageChangedEventArgs());
        }
        catch(QException &)
        {

        }
    }
}

void Image_Module::LoadFromPngFile(QString filePath, GrayImage *image)
{
    QFileInfo info(filePath);
    QString filename = info.baseName() + ".png";
    QString path = info.absoluteDir().absolutePath() + filename;
    QFile file(path);
    if(file.exists(path))
        {
            QImage imageSource(path);
            try
            {
                int width = imageSource.width();
                int height = imageSource.height();
                int stride = imageSource.bytesPerLine();
                quint8 *scan0 = imageSource.bits();
                image->resizeImage(width, height);
                quint16 *data = image->data().get();
                int imgWidth = image->width();
                int imgHeight = image->height();
                int offset = stride - width * 3;
                quint8 *p = scan0;
                for(int y = 0; y < height; ++y)
                {
                    for(int x = 0; x < width; ++x)
                    {
                        *(data + y * width + x) = static_cast<quint16>(10 * *(p++));
                        ++p;
                        ++p;
                    }
                    p += offset;
                }
                data = nullptr;
                bool *validRow = image->validRow().data();
                for(int i = 0; i < image->height(); ++i)
                {
                    *(validRow + i) = true;
                }
                validRow = nullptr;
                emit image->evImageChanged(image, ImageChangedEventArgs());
            }
            catch(QException &)
            {

            }
        }
}

QString BytesToAny::QByteArrayToHexString(const QByteArray &data)
{
    QString ret(data.toHex().toUpper());
    int len = ret.length() / 2;
    for (int i = 1; i < len; i++)
    {
        ret.insert(2 * i + i - 1, " ");
    }
    return ret;
}

int BytesToAny::toInt(const quint8 *data)
{
    return (int)(((*(data + 3) << 24) & 0xFF000000)
                + ((*(data + 2) << 16) & 0x00FF0000)
                    + ((*(data + 1) << 8) & 0x0000FF00)
                        + ((*(data + 0)) & 0x000000FF));
}

quint16 BytesToAny::toQUint16(const quint8 *data)
{
    return (quint16)(((*(data + 1) << 8) & 0xFF00)
                        + ((*(data + 0)) & 0x00FF));
}

int BytesToAny::toQInt16(const quint8 *data)
{
    return (qint16)(((*(data + 1) << 8) & 0xFF00)
                        + ((*(data + 0)) & 0x00FF));
}

quint32 BytesToAny::toQUint32(const quint8 *data)
{
    return (quint32)(((*(data + 3) << 24) & 0xFF000000)
                + ((*(data + 2) << 16) & 0x00FF0000)
                    + ((*(data + 1) << 8) & 0x0000FF00)
                        + ((*(data + 0)) & 0x000000FF));
}

void IniFile::WriteIniFile(const QString &section, const QString &name, const QVariant &value, const QString &path)
{
    QSettings settings(path, QSettings::Format::IniFormat);
    settings.setValue(section + "/" + name, value);
}

QVariant IniFile::ReadIniFile(const QString &section, const QString &name, const QVariant &defaultValue, const QString &path)
{
    QFile file(path);
    if(!file.exists())
        return defaultValue;
    QSettings settings(path, QSettings::Format::IniFormat);
    settings.beginGroup(section);
    return settings.value(name, defaultValue);
}

void IniFile::InitIniFile()
{
    if(!QDir(GlobalPath::localFilePath + "/config/").exists())
    {
        QDir dir;
        dir.mkdir(GlobalPath::localFilePath + "/config/");
    }
    QFile file(IniFile::IniFileName);
    if(file.exists())
        return;
    IniFile::WriteIniFile(QString("SerialPort"), QString("PortName"), QVariant("COM1") ,IniFile::IniFileName);
    IniFile::WriteIniFile(QString("SerialPort"), QString("BaudRate"), QVariant(QSerialPort::Baud9600), QString(IniFile::IniFileName));
    IniFile::WriteIniFile(QString("SerialPort"), QString("DataBits"), QVariant(QSerialPort::Data8), QString(IniFile::IniFileName));
    IniFile::WriteIniFile(QString("SerialPort"), QString("StopBits"), QVariant(QSerialPort::OneStop), QString(IniFile::IniFileName));
    IniFile::WriteIniFile(QString("SerialPort"), QString("Parity"), QVariant(QSerialPort::NoParity), QString(IniFile::IniFileName));
}

double Sensor_Module::pressureToPsi(int value)
{
    double valueTmp = (double)value * 1000;
    double bar = (valueTmp / (1 << 22)) / 1000;
    return bar * 14.5137881;
}

double Sensor_Module::pressureToMBar(int value)
{
    double valueTmp = (double)value * 1000;
    double mbar = (valueTmp / (1 << 22));
    return mbar;
}

//double Sensor_Module::pressureToPsi(int value)
//{
//    double bar = (((value * 1000) / 2) << 22) / 1000;
//    return bar * 14.5137881;
//}

int Fluidics_Module::ulPerMinToStepPerSec(double value)
{
    return qRound(value / 60 * 6);
}
