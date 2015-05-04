#include "fileloader.h"

#include <QDir>
#include <QDirIterator>
#include <QtDebug>

#include "settings.h"

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

        if(this->m_hide && this->m_selectedItems.contains(iter.filePath()))
            continue;

        this->m_itemsList.append(iter.filePath());
    }

    this->m_itemsList.sort();

    qDebug() << "Skiped items" << this->m_selectedItems.count();
    qDebug() << this->m_selectedItems;
    qDebug() << "Load items" << this->m_itemsList.count();

    emit this->imageModelChanged();
}

ImageModel *FileLoader::imageModel() const
{
    QList<QSharedPointer<ImageData> > list;

    Q_FOREACH(QString path, this->m_itemsList)
    {
        list.append(QSharedPointer<ImageData>(
                        new ImageData(path, QFileInfo(path).fileName(), this->m_selectedItems.contains(path))));
    }

    return new ImageModel(list);
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
    this->loadImageList(this->m_lastPath);
}

void FileLoader::saveSelectedItems(QString user)
{
    QStringList list = this->m_selectedItems.toList();
    QStringList out;

    Q_FOREACH(QString path, list)
    {
        out << this->reducePath(path);
    }

    Settings::instance()->setUserSelectedList(user, out);
}

void FileLoader::loadSelectedItems(QString user)
{
    QStringList list;

    qDebug() << "Loading selected items for user" << user;

    list = Settings::instance()->userSelectedList(user);
    this->m_selectedItems.clear();

    Q_FOREACH(QString item, list)
    {
        this->m_selectedItems.insert(this->expandPath(item));
    }

    qDebug() << "loaded select items:" << this->m_selectedItems;
}

/** Private methods **/
QString FileLoader::reducePath(QString &path)
{
    qDebug() << this->m_lastPath;
    path.remove(this->m_lastPath);

    return path;
}

QString FileLoader::expandPath(QString &path)
{
    path += this->m_lastPath + path;

    return path;
}
