#include <QApplication>
#include <QQmlApplicationEngine>
#include <QtQml>

#include "fileloader.h"
#include "imagemodel.h"
#include "settings.h"

static QObject *sigletonProvider(QQmlEngine *engine, QJSEngine *jsEngine)
{
    Q_UNUSED(engine)
    Q_UNUSED(jsEngine)

    return Settings::instance();
}

void registerQmlTypes()
{
    qmlRegisterType<FileLoader>("org.ps.EasyImage", 1, 0, "FileLoader");
    qmlRegisterUncreatableType<ImageModel>("org.ps.EasyImage", 1, 0, "ImageModel",
                                           "Will be created by FileLoader");
    qmlRegisterSingletonType<Settings>("org.ps.EasyImage", 1, 0, "Settings",
                                       sigletonProvider);
}

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    registerQmlTypes();

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));


    return app.exec();
}
