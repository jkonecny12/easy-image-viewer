#include "settings.h"

#include <QtDebug>

Settings *Settings::s_instance = new Settings();

Settings::Settings(QObject *parent) :
    QSettings(QSettings::Scope::UserScope,
              QStringLiteral("PacketSeekers"),
              QStringLiteral("easy-image-viewer"),
              parent)
{
    QStringList usersList = this->users();

    if(usersList.isEmpty())
        this->m_activeUser.clear();

    this->m_activeUser = usersList[0];
}

Settings::~Settings()
{
}

Settings *Settings::instance()
{
    return Settings::s_instance;
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
        list << user;
        setValue(this->c_USERS, QVariant(list));
        emit this->usersChanged();
    }
}

QStringList Settings::userSelectedList(QString user)
{
    QStringList groups = childGroups();
    QStringList ret;

    if(groups.contains(user))
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

QString Settings::activeUser() const
{
    return this->m_activeUser;
}

void Settings::setActiveUser(QString user)
{
    if(user != this->m_activeUser)
    {
        this->m_activeUser = user;
        emit this->activeUserChanged();
    }
}
