#include "fileloader.h"

#include <QDir>
#include <QDirIterator>
#include <QtDebug>

FileLoader::FileLoader(QObject *parent) :
    QObject(parent),
    m_hide(true)
{
}

FileLoader::~FileLoader()
{
}

void FileLoader::loadImageList(QString path)
{
    path.remove(QStringLiteral("file://"));
    path.remove(QStringLiteral("qrc:"));

    this->m_lastPath = path;

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

        if(this->m_hide && this->m_selectedItems.contains(iter.path()))
            continue;

        this->m_itemsList.append(iter.filePath());
        this->m_categories.insert(iter.fileName().left(3));
    }

    this->m_itemsList.sort();

    qDebug() << "Load items" << this->m_itemsList.count();

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

void FileLoader::selectImage(QString path)
{
    this->m_selectedItems.insert(path);
}

void FileLoader::unselectImage(QString path)
{
    this->m_selectedItems.remove(path);
}

/** SLOTS **/

void FileLoader::hideItems(bool hide)
{
    this->m_hide = hide;

    if(this->m_hide)
    {
        this->loadImageList(this->m_lastPath);
    }
}
