#include "imagemodel.h"

#include <QtDebug>
#include <QFileInfo>

ImageModel::ImageModel() :
    QAbstractListModel()
{

}

ImageModel::ImageModel(const QStringList &paths) :
    QAbstractListModel()
{
    Q_FOREACH(QString path, paths)
    {
        this->m_imageList.append(qMakePair(QFileInfo(path).fileName(), path));
    }
}

void ImageModel::addImage(const QString path)
{
    this->m_imageList.append(qMakePair(path, QFileInfo(path).fileName()));
}

int ImageModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return this->m_imageList.count();
}

QVariant ImageModel::data(const QModelIndex &index, int role) const
{
    if(!index.isValid() || index.row() >= this->m_imageList.count())
        return QVariant();

    switch(role)
    {
    case Qt::DisplayRole:
    case ImageName:
        return QVariant(this->m_imageList.at(index.row()).first);
    case ImagePath:
        return QVariant(this->m_imageList.at(index.row()).second);
    default:
        return QVariant();
    }
}

QHash<int, QByteArray> ImageModel::roleNames() const
{
    QHash<int, QByteArray> roles;

    roles[ImageName] = "name";
    roles[ImagePath] = "path";

    return roles;
}
