#ifndef IMAGEMODEL_H
#define IMAGEMODEL_H

#include <QObject>
#include <QAbstractListModel>
#include <QList>
#include <QSharedPointer>

struct ImageData;
class ImageModel : public QAbstractListModel
{
    Q_OBJECT
public:
    enum ImageRoles {
        ImageName = Qt::UserRole +1,
        ImagePath,
        ImageSelected
    };

    explicit ImageModel();
    explicit ImageModel(const QStringList &paths);

    int rowCount(const QModelIndex &parent) const Q_DECL_OVERRIDE;

    QVariant data(const QModelIndex &index, int role) const Q_DECL_OVERRIDE;

    QHash<int, QByteArray> roleNames() const Q_DECL_OVERRIDE;

private:
    QList<QSharedPointer<ImageData> > m_imageList;
};

#endif // IMAGEMODEL_H
