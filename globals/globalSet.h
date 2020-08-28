#ifndef GLOBALSET_H
#define GLOBALSET_H
#include <qglobal.h>
#include <QImage>
#include <memory>
#include <QString>
#include <QDebug>
#include <QVector>
#include <QDir>
#include <QFile>
#include <QFileInfo>
#include <QFileDevice>
#include <QDataStream>
#include <QException>
#include <QIODevice>
#include <QReadWriteLock>
#include <utility>
#include <QCoreApplication>
#include <QSettings>
#include <QSerialPort>
#include <memory>
#include "onOff.h"
#include "enums.h"
#include "Responses/response.h"
#include "Tools/applicationexception.h"
class ImageBase;
class GrayImage;
/**
 * @brief DebugOut debug输出屏幕
 */
#ifdef DEBUG
#define DebugOut(msg)\
{qDebug() << __FILE__ << __LINE__  << __FUNCTION__ << msg << endl;}
#else
#define DebugOut(msg)
#endif
namespace GlobalPath {
    extern const QString localFilePath;
}

namespace BytesToAny {
    QString QByteArrayToHexString(const QByteArray& data);
    int toInt(const quint8 *data);
    int toQInt16(const quint8 *data);
    quint16 toQUint16(const quint8 *data);
    quint32 toQUint32(const quint8 * data);
}

void registerType();
namespace IniFile {
    extern const QString IniFileName;
    void InitIniFile();
    void WriteIniFile(const QString& section, const QString& name, const QVariant& value, const QString& path);
    QVariant ReadIniFile(const QString& section, const QString& name, const QVariant& defaultValue, const QString& path);
}
namespace Image_Module {
    const int MapBufferSize = 50 * 1024;
    const int bytesPerPixel = 2;
    const quint16 BlankColor = 1024;
    typedef struct imageStruct{
    public:
        const int BytesPerPixel = 2;
        std::shared_ptr<quint16> data;
        quint32 width;
        quint32 height;
    }ImageStruct;
    struct ImageLocker
    {
    public:
        static QReadWriteLock _multiImageWithSameNameLock;
    };
   struct Header{
    public:
        void write(QDataStream &writer);
        void write(QByteArray &writer);
    private:
        quint8 _formatID1;
        quint8 _formatID2;
        quint16 _tiffID;
        quint32 _offsetToIFD;
    };

    struct IFD{
    public:
        IFD(Global::TAG tag, Global::Type type, quint32 count, quint32 value);
    public:
        void write(QDataStream &writer);
        void write(QByteArray &writer);
    public:
        const Global::TAG _tag;
        const Global::Type _type;
        const quint32 _count;
        quint32 _value;
    };
    void LoadCompressedImage(QString filePath, GrayImage *image);
    void LoadFromPngFile(QString filePath, GrayImage *image);
    void LoadFromTiffFile(ImageBase *imageBase, const QString &fileName);
    void SaveChunkAsTiffFile(quint16 *imagePtr, int imageWidth, int linesToWrite, const QString& fileName, Image_Module::OverwriteHandling overwriteHandling);
    void SaveAsTiffFile(ImageBase *image, const QString &fileName, Image_Module::OverwriteHandling);
    void SaveAsTiffFile(ImageStruct imageStruct, const QString &fileName, Image_Module::OverwriteHandling overwriteHandling);
    void BackupCurrentFile(const QString& currentPath);
    void GetNewFileName(const QString& fileName);
//    void SaveAsTiffFile()
}
// namespace Image_Modulse
namespace Fluidics_Module {
    const int stepsPerUl = 6;
    const int fullScaleVolume = 500;
    int ulPerMinToStepPerSec(double value);
}
namespace Sensor_Module {
//    extern const int pressureMaintainingInspectionCycleLimit;
//    extern const int pressureMaintainingThreshold; //psi
    /**
     * @brief pressureToPsi 将下位机返回值转为psi
     * @param value         下位机返回值
     * @return              psi
     */
    double pressureToPsi(int value);
    double pressureToMBar(int value);
} // namespace Sensor_Module
namespace Debug_Module {
}
#endif // GLOBALSET_H
