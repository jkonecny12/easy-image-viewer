#include "imagemodel.h"

#include <QtDebug>

ImageModel::ImageModel()
{

}

ImageModel::ImageModel(const QString path, const QString name)
{
    this->m_listNames.append(name);
    this->m_listPaths.append(path);
}

int ImageModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return this->m_listNames.count();
}

QVariant ImageModel::data(const QModelIndex &index, int role) const
{
    if(!index.isValid() || index.row() >= this->m_listNames.count())
        return QVariant();

    switch(role)
    {
    case Qt::DisplayRole:
    case ImageName:
        return QVariant(this->m_listNames.at(index.row()));
    case ImagePath:
        return QVariant(this->m_listPaths.at(index.row()));
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
