#ifndef IMAGEMODEL_H
#define IMAGEMODEL_H

#include <QObject>
#include <QAbstractListModel>
#include <QList>
#include <QSharedPointer>

/** Data struct with information about Image **/
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

/** Main ImageModel class **/
class ImageModel : public QAbstractListModel
{
    Q_OBJECT
public:
    enum ImageRoles {
        ImageName = Qt::UserRole +1, // name
        ImagePath,                   // path
        ImageSelected                // selected
    };

    explicit ImageModel();
    explicit ImageModel(const QList<QSharedPointer<ImageData> > imageList);

    int rowCount(const QModelIndex &parent) const Q_DECL_OVERRIDE;

    QVariant data(const QModelIndex &index, int role) const Q_DECL_OVERRIDE;

    QHash<int, QByteArray> roleNames() const Q_DECL_OVERRIDE;

    void setSelected(QString path, bool selected);

private:
    const QList<QSharedPointer<ImageData> > m_imageList;
};

#endif // IMAGEMODEL_H
