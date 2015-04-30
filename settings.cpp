#include "settings.h"

Settings::Settings(QObject *parent) :
    QSettings(QSettings::Scope::UserScope,
              QStringLiteral("PacketSeekers"),
              QStringLiteral("easy-image-viewer"),
              parent)
{
}

Settings::~Settings()
{
}

QString Settings::rootLocation() const
{
    return this->value(QStringLiteral("rootFolder")).toString();
}

void Settings::setRootLocation(QString path)
{
    path.remove(QStringLiteral("file://"));
    QString oldLocation = rootLocation();

    if(oldLocation != path)
    {
        this->setValue(QStringLiteral("rootFolder"), QVariant(path));
        emit this->rootLocationChanged(path);
    }
}
