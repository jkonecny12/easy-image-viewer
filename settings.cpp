#include "settings.h"

#include <QtDebug>

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
    return this->value(this->c_ROOT_FOLDER).toString();
}

void Settings::setRootLocation(QString path)
{
    path.remove(QStringLiteral("file://"));
    QString oldLocation = rootLocation();

    if(oldLocation != path)
    {
        this->setValue(this->c_ROOT_FOLDER, QVariant(path));
        emit this->rootLocationChanged(path);
    }
}

QStringList Settings::users() const
{
    return value(this->c_USERS).toStringList();
}

void Settings::addUser(QString user)
{
    qDebug() << "add user:" << user;
    QStringList list = this->users();

    if(!list.contains(user))
    {
        setValue(this->c_USERS, QVariant(user));
        emit this->usersChanged();
    }
}

QStringList Settings::userSelectedList(QString user)
{
    QStringList groups = childGroups();
    QStringList ret;

    if(!groups.contains(user))
    {
        beginGroup(user);
        ret = value(this->c_SELECTED_ITEMS).toStringList();
        endGroup();
    }
    return ret;
}

void Settings::setUserSelectedList(QString user, QStringList userList)
{
    beginGroup(user);
    setValue(this->c_SELECTED_ITEMS, QVariant(userList));
    endGroup();
}
