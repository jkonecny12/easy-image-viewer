#include <QApplication>
#include <QQmlApplicationEngine>
#include <QtQml>

#include "fileloader.h"
#include "imagemodel.h"
#include "categorymodel.h"
#include "settings.h"

void registerQmlTypes()
{
    qmlRegisterType<FileLoader>("org.ps.EasyImage", 1, 0, "FileLoader");
    qmlRegisterType<ImageModel>("org.ps.EasyImage", 1, 0, "ImageModel");
                                           //"Will be created by FileLoader");
    qmlRegisterUncreatableType<CategoryModel>("org.ps.EasyImage", 1, 0, "CategoryModel",
                                              "Will be created by FileLoader");
    qmlRegisterType<Settings>("org.ps.EasyImage", 1, 0, "Settings");
}

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    registerQmlTypes();

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));


    return app.exec();
}
