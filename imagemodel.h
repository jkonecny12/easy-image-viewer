#ifndef IMAGEMODEL_H
#define IMAGEMODEL_H

#include <QObject>
#include <QAbstractListModel>
#include <QList>
#include <QPair>

class ImageModel : public QAbstractListModel
{
    Q_OBJECT
public:
    enum ImageRoles {
        ImageName = Qt::UserRole +1,
        ImagePath
    };

    explicit ImageModel();
    explicit ImageModel(const QStringList &paths);

    void addImage(const QString path);

    int rowCount(const QModelIndex &parent) const Q_DECL_OVERRIDE;

    QVariant data(const QModelIndex &index, int role) const Q_DECL_OVERRIDE;

    QHash<int, QByteArray> roleNames() const Q_DECL_OVERRIDE;

private:
    QList<QPair<QString, QString> > m_imageList;
};

#endif // IMAGEMODEL_H
