TEMPLATE = app

QT += qml quick widgets

SOURCES += main.cpp \
    fileloader.cpp \
    imagemodel.cpp \
    settings.cpp

RESOURCES += qml.qrc

CONFIG += c++11

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)

HEADERS += \
    fileloader.h \
    imagemodel.h \
    settings.h
