#include "fileloader.h"

#include <QDir>
#include <QDirIterator>
#include <QtDebug>

FileLoader::FileLoader(QObject *parent) :
    QObject(parent)
{

}

FileLoader::~FileLoader()
{

}

void FileLoader::loadImageList(QString path)
{
    path.remove(QStringLiteral("file://"));
    path.remove(QStringLiteral("qrc:"));

    qDebug() << "Load folder: " + path;

    QDir dir = QDir(path);
    dir.setFilter(QDir::Filter::Files);
    QStringList filters({"*.png"});
    dir.setNameFilters(filters);

    if(!dir.exists())
        return;

    QDirIterator iter(dir);

    this->m_itemsList.clear();

    while(iter.hasNext())
    {
        iter.next();
        qDebug() << "Loaded: " << iter.filePath();
        this->m_itemsList.append(iter.filePath());
    }

    this->m_itemsList.sort();

    emit imageModelChanged();
}

ImageModel *FileLoader::imageModel() const
{
    return new ImageModel(this->m_itemsList);
}
