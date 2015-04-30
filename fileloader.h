#ifndef FILELOADER_H
#define FILELOADER_H

#include <QObject>
#include <QStringList>

#include "imagemodel.h"

class FileLoader : public QObject
{
    Q_OBJECT
    Q_PROPERTY(ImageModel* imageModel READ imageModel NOTIFY imageModelChanged)

public:
    explicit FileLoader(QObject *parent = 0);
    ~FileLoader();

    Q_INVOKABLE void loadImageList(QString path);

    Q_INVOKABLE ImageModel *imageModel() const;

signals:
    void imageModelChanged();

public slots:

private:
    QStringList m_itemsList;
};

#endif // FILELOADER_H
