#include <QGuiApplication>
#include <QApplication>
#include <QQmlApplicationEngine>
#include "globals/enums.h"
#include "globals/globalSet.h"
#include "globals/qmlaggregator.h"
#include "Commands/command.h"
#include "Commands/bubblecalibrate_command.h"
#include "Responses/bubblecalibrate_command_response.h"
#include <QVariant>
#include <QPixmap>
//#include <QFileInfo>
#include <functional>
#include <typeinfo>
#include <utility>
#include "Responses/audio_command_response.h"
#include "Commands/camerasnap_command.h"
#include "commands/bubblemeasureflighttime_command.h"
#include "Responses/bubblemeasureflighttime_command_response.h"
#include "Tools/imagebase.h"
#include "Tools/grayimage.h"
#include "Commands/pumpinit_command.h"
QList<Command *>commands;
void testMethod();
//void testEnum();
void testFile();
void testResponse();
using namespace Image_Module;
int main(int argc, char *argv[])
{
    registerType();
    registerOperatorInQml();
    //Audio_Command_Response *reponse = new Audio_Command_Response();
    IniFile::InitIniFile();
    //Command *command = new PumpInit_Command();
    //Command *command = new BubbleMeasureFlightTime_Command(nullptr, , -1, CommunicateCoreUnderlying::BubbleDeviceId::LANEASENSOR);
    //command->sendCommand();
    //    int vali = 0;
//    QByteArray bt;
//    bt.append((char)8);
//    bt.append((char)0);
//    bt.append((char)0);
//    bt.append((char)0);
//    memcpy(&vali, bt.data(), sizeof(int));
//    DebugOut(vali);
//    testFile();
//    testResponse();
//    CameraSnap_Command *p1 = new CameraSnap_Command();
//    QVector<quint32> a = p1->exposure_usec();

//    QVector<IFD> directoryEntries{
//        IFD(Global::TAG::NEWSUBFILETYPE, Global::Type::LONG, 1u, 0u),
//        IFD(Global::TAG::IMAGEWIDTH, Global::Type::LONG, 1u, 100),
//        IFD(Global::TAG::IMAGELENGTH, Global::Type::LONG, 1u, 100),
//        IFD(Global::TAG::BITSPERSAMPLE, Global::Type::SHORT, 1u, 16u),
//        IFD(Global::TAG::COMPRESSION, Global::Type::SHORT, 1u, 1u),
//        IFD(Global::TAG::PHOTOMETRICINTERPRETATION, Global::Type::SHORT, 1u, 1u),
//        IFD(Global::TAG::STRIPOFFSETS, Global::Type::LONG, 1u, 0u),
//        IFD(Global::TAG::SAMPLESPERPIXEL, Global::Type::SHORT, 1u, 1u),
//        IFD(Global::TAG::ROWSPERSTRIP, Global::Type::LONG, 1u, 100),
//        IFD(Global::TAG::STRIPBYTECOUNTS, Global::Type::LONG, 1u, (100 * 100 * 2))
//    };
//    int offsetToImageData = sizeof(Header) + directoryEntries.size() * sizeof(IFD) + 4;
//    DebugOut(offsetToImageData);
    //Image_Module::IFD *ifd1 = new Image_Module::IFD(Global::TAG::ARTIST, Global::Type::ASCII, 3, 4) ;
    //ImageBase *img = new GrayImage();
    //img->width();
   // BubbleCalibrate_Command *p = new BubbleCalibrate_Command(nullptr, QVariant::fromValue(8), 0);
    //p = new BubbleCalibrate_Command(nullptr, QVariant::fromValue(8), 0);
//    QVariant var = QVariant::fromValue(testEnum::x);
//    testEnum tes = var.value<testEnum>();
//    QVariant var = QVariant::fromValue(testEnum::x);
//    testEnum tes = var.value<testEnum>();
//    testMethod();


    /*Response response;
    std::function<void (int)>func = std::bind(&Response::setId, &response, std::placeholders::_1);
    func(100);*/
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QApplication app(argc, argv);

    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);
    return app.exec();
}
void testCommandResponse()
{
    Response *res;
//    Response resp;
//    res.setValue(resp);
    Command *command = new BubbleCalibrate_Command(nullptr, res, -1);
    commands.append(std::move(command));
}
void testResponse()
{
//    QVariant var;
//    var.setValue(Response());
//    Response res = var.value<Response>();

    Response *response = new Audio_Command_Response();
    //qDebug() << QString::fromStdString(typeid(*response).name()).mid(6) << endl;
    QVariant var = QVariant::fromValue(*response);
    //qDebug() << var. << endl;
    Response *rsp = &(var.value<Response>());
    Response rs = var.value<Response>();
    qDebug() << rs.typeName()<<endl;
    //qDebug() << rsp->typeName() << endl;
}

void testImage(){
    GrayImage *image = new GrayImage(2592, 1944);
    QVector<QVector<quint16>>datas;
    datas.resize(1944);;
    for(int i = 0; i < datas.size(); ++i)
    {
        datas[i].resize(2592);
        for(int j = 0; j < datas[i].size(); ++j)
        {
            datas[i][j] = 100;
        }
    }
    image->setData(datas);
    //Image_Module::BackupCurrentFile("D:\\TFS\\LaserSpotFilter_Expose\\1.0.0\\LaserSpotFilter_OpenCV\\AutoFocusError_QtOpencv\\123.tif");
    std::shared_ptr<quint16> data = image->data();
    image->loadedImage("D:\\TFS\\LaserSpotFilter_Expose\\1.0.0\\LaserSpotFilter_OpenCV\\AutoFocusError_QtOpencv\\FlatFieldCorrectionImage_20190408150040_red_LED_1_1_0_01001.tif");
    GrayImage *imagePtr = image->rotateImage(45);
    qint64 start = QDateTime::currentMSecsSinceEpoch();
    //Image_Module::LoadFromTiffFile(image, "D:\\TFS\\LaserSpotFilter_Expose\\1.0.0\\LaserSpotFilter_OpenCV\\AutoFocusError_QtOpencv\\FlatFieldCorrectionImage_20190408150040_red_LED_1_1_0_01001.tif");
    //image->rotateImage(45);
    imagePtr->saveImage("D:\\TFS\\LaserSpotFilter_Expose\\1.0.0\\LaserSpotFilter_OpenCV\\AutoFocusError_QtOpencv\\test.tif");
    qint64 end = QDateTime::currentMSecsSinceEpoch();
    DebugOut(end - start);
    //QImage qimg;
   // QMatrix mat;
   //
    delete image;
    delete imagePtr;
}

void testPath()
{
    QFileInfo fileInfo;
    fileInfo.setFile("c:\\abc\\bbb\\ccc\\efg.cfg");
    QString dirName = fileInfo.absolutePath();
    QDir dir;
    dir.setPath(dirName);
    QString s = dir.exists()?":true":":false";
    DebugOut(dirName + s);
}

void testFile()
{
    int offsetToImageData = 132;
    qint64 dtStart = QDateTime::currentMSecsSinceEpoch();
    QFile file("abc.dat");
    if(file.open(QIODevice::ReadWrite))
    {
        QByteArray writer;
        Header header;
        header.write(writer);
        writer.append((char)80);
        writer.append(reinterpret_cast<char*>(static_cast<quint32>(0)));
        std::shared_ptr<char>datapool = std::shared_ptr<char>(new char[512],[](char *p){delete[] p;});
        memcpy(datapool.get(), writer.data(), 512);
        quint8 *p = file.map(0, 512);
        if(p)
        {
            memcpy(p, datapool.get(), 512);
            file.unmap(p);
            p = nullptr;
        }
        qint64 imageSize = 10 * 1024 * 1024;
        quint8 *imagePtr = new quint8[imageSize];
        for(int i = 0; i< imageSize; ++i)
        {
            *(imagePtr + i) = i % 1000;
        }
        file.resize(offsetToImageData + 10 * 1024 * 1024);
        quint32 begin = 0;
        while(imageSize > 0)
        {
//            DebugOut(imageSize);
            p = file.map(offsetToImageData, imageSize > Image_Module::MapBufferSize ? Image_Module::MapBufferSize:imageSize);
            memcpy(p, imagePtr + begin, imageSize > Image_Module::MapBufferSize ? Image_Module::MapBufferSize:imageSize);
            imageSize -= Image_Module::MapBufferSize;
            offsetToImageData += Image_Module::MapBufferSize;
            begin += Image_Module::MapBufferSize;
            file.unmap(p);
            p = nullptr;
        }
        file.close();
    }
    qint64 dtEnd = QDateTime::currentMSecsSinceEpoch();
    DebugOut(dtEnd - dtStart);
}
