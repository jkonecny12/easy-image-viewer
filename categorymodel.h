#ifndef CATEGORYMODEL_H
#define CATEGORYMODEL_H

#include <QObject>
#include <QAbstractListModel>
#include <QStringList>

class CategoryModel : public QAbstractListModel
{
    Q_OBJECT
public:
    enum CategoryRoles {
        CategoryPrefix = Qt::UserRole +1, // categoryPrefix
        Name // name -- will be used later
    };

    explicit CategoryModel(QObject *parent = 0);
    explicit CategoryModel(QStringList categories, QObject *parent = 0);
    ~CategoryModel();

    int rowCount(const QModelIndex &parent) const Q_DECL_OVERRIDE;

    QVariant data(const QModelIndex &index, int role) const Q_DECL_OVERRIDE;

    QHash<int, QByteArray> roleNames() const Q_DECL_OVERRIDE;

private:
    QStringList m_categoryList;
};

#endif // CATEGORYMODEL_H
