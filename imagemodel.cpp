#include "imagemodel.h"

#include <QtDebug>
#include <QFileInfo>

/** Inner class to store information about Image **/
struct ImageData {
    QString path;
    QString name;
    bool isSelected;

    ImageData(QString path, QString name, bool isSelected) :
        path(path),
        name(name),
        isSelected(isSelected)
    {
    }

    virtual ~ImageData()
    {
    }
};

/** Main Image model **/

ImageModel::ImageModel() :
    QAbstractListModel()
{

}

ImageModel::ImageModel(const QStringList &paths) :
    QAbstractListModel()
{
    Q_FOREACH(QString path, paths)
    {
        this->m_imageList.append(QSharedPointer<ImageData>(new ImageData(path, QFileInfo(path).fileName(), false)));
    }
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
        return QVariant(this->m_imageList.at(index.row())->name);
    case ImagePath:
        return QVariant(this->m_imageList.at(index.row())->path);
    case ImageSelected:
        return QVariant(this->m_imageList.at(index.row())->isSelected);
    default:
        return QVariant();
    }
}

QHash<int, QByteArray> ImageModel::roleNames() const
{
    QHash<int, QByteArray> roles;

    roles[ImageName] = "name";
    roles[ImagePath] = "path";
    roles[ImageSelected] = "selected";

    return roles;
}
