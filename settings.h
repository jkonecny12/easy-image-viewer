#ifndef SETTINGS_H
#define SETTINGS_H

#include <QObject>
#include <QSettings>
#include <QStringList>

class Settings : public QSettings
{
    Q_OBJECT

    Q_PROPERTY(QString rootLocation READ rootLocation WRITE setRootLocation NOTIFY rootLocationChanged)
    Q_PROPERTY(QStringList users READ users NOTIFY usersChanged)
    Q_PROPERTY(QString activeUser READ activeUser WRITE setActiveUser NOTIFY activeUserChanged)
public:
    ~Settings();

    static Settings *instance();

    QString rootLocation() const;
    void setRootLocation(QString path);

    QStringList users() const;
    Q_INVOKABLE void addUser(QString user);

    QStringList userSelectedList(QString user);
    void setUserSelectedList(QString user, QStringList userList);

    QString activeUser() const;
    void setActiveUser(QString user);

signals:
    void rootLocationChanged(QString);
    void usersChanged();
    void activeUserChanged();

private:
    explicit Settings(QObject *parent = 0);

private:
    QString c_ROOT_FOLDER = QStringLiteral("rootFolder");
    QString c_USERS = QStringLiteral("users");
    QString c_SELECTED_ITEMS = QStringLiteral("selectedItems");
    static Settings *s_instance;

    QString m_activeUser;
};

#endif // SETTINGS_H
