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
    QStringList filters({"*.png", "*.jpg"});
    dir.setNameFilters(filters);

    if(!dir.exists())
        return;

    QDirIterator iter(dir);

    this->m_itemsList.clear();

    while(iter.hasNext())
    {
        iter.next();
        this->m_itemsList.append(iter.filePath());
        this->m_categories.insert(iter.fileName().left(3));
    }

    this->m_itemsList.sort();

    emit this->categoryModelChanged();
}

CategoryModel *FileLoader::categoryModel() const
{
    QStringList list = this->m_categories.toList();
    list.sort();

    return new CategoryModel(list);
}

ImageModel *FileLoader::imageModel(QString categoryPrefix) const
{
    QStringList categoryImages;

    Q_FOREACH(QString path, this->m_itemsList)
    {
        QString fileName = QFileInfo(path).fileName();

        if(fileName.startsWith(categoryPrefix))
            categoryImages << path;
    }

    return new ImageModel(categoryImages);
}
