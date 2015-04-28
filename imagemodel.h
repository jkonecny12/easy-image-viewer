#ifndef IMAGEMODEL_H
#define IMAGEMODEL_H

#include <QObject>
#include <QAbstractListModel>
#include <QStringList>

class ImageModel : public QAbstractListModel
{
    Q_OBJECT
public:
    enum ImageRoles {
        ImageName = Qt::UserRole +1,
        ImagePath
    };

    explicit ImageModel();
    explicit ImageModel(const QString path, const QString name);

    int rowCount(const QModelIndex &parent) const Q_DECL_OVERRIDE;

    QVariant data(const QModelIndex &index, int role) const Q_DECL_OVERRIDE;

    QHash<int, QByteArray> roleNames() const Q_DECL_OVERRIDE;

private:
    QStringList m_listPaths;
    QStringList m_listNames;
};

#endif // IMAGEMODEL_H
