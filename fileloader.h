#ifndef FILELOADER_H
#define FILELOADER_H

#include <QObject>
#include <QStringList>
#include <QSet>

#include "imagemodel.h"

class FileLoader : public QObject
{
    Q_OBJECT

    Q_PROPERTY(ImageModel* imageModel READ imageModel NOTIFY imageModelChanged)
public:
    explicit FileLoader(QObject *parent = 0);
    ~FileLoader();

    Q_INVOKABLE void loadImageList(QString path);

    ImageModel *imageModel() const;

    Q_INVOKABLE void selectImage(QString path);
    Q_INVOKABLE void unselectImage(QString path);

signals:
    void imageModelChanged();

public slots:
    void hideItems(bool hide);

    void saveSelectedItems(QString user);
    void loadSelectedItems(QString user);

private:
    QString reducePath(QString &path);
    QString expandPath(QString &path);

private:
    QStringList m_itemsList;
    QSet<QString> m_selectedItems;
    bool m_hide;
    QString m_lastPath;
};

#endif // FILELOADER_H
