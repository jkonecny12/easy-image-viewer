#ifndef SETTINGS_H
#define SETTINGS_H

#include <QObject>
#include <QSettings>

class Settings : public QSettings
{
    Q_OBJECT

    Q_PROPERTY(QString rootLocation READ rootLocation WRITE setRootLocation NOTIFY rootLocationChanged)
public:
    explicit Settings(QObject *parent = 0);
    ~Settings();

    QString rootLocation() const;
    void setRootLocation(QString path);

signals:
    void rootLocationChanged(QString);
};

#endif // SETTINGS_H
