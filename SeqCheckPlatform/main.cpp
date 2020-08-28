#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QDomDocument>
#include <QFile>
#include<QStandardPaths>

int main(int argc, char *argv[])
{
    QDomDocument dom;
    QFile file(QStandardPaths::standardLocations(QStandardPaths::AppDataLocation)[0]+"/SeqCheckPlatform/AirDetecttest.xml");
    if (!file.open(QFile::ReadOnly | QFile::Text))
    {

    }
    QString errorStr;
    int errorLine;
    int errorColumn;
    if (!dom.setContent(&file, false, &errorStr, &errorLine, &errorColumn))
    {
//        std::cerr << "Error: Parse error at line " << errorLine << ", "
//                  << "column " << errorColumn << ": "
//                  << qPrintable(errorStr) << std::endl;
        return false;
    }
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

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
