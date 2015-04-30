#include "categorymodel.h"

CategoryModel::CategoryModel(QObject *parent) :
    QAbstractListModel(parent)
{

}

CategoryModel::CategoryModel(QStringList categories, QObject *parent) :
    QAbstractListModel(parent)
{
    Q_FOREACH(QString prefix, categories)
    {
        this->m_categoryList.append(prefix);
    }
}

CategoryModel::~CategoryModel()
{

}

int CategoryModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);

    return this->m_categoryList.count();
}

QVariant CategoryModel::data(const QModelIndex &index, int role) const
{
    if(!index.isValid() || index.row() > this->m_categoryList.count())
        return QVariant();

    switch(role)
    {
    case CategoryRoles::CategoryPrefix:
        return QVariant(this->m_categoryList.at(index.row()));
    case CategoryRoles::Name:
        return QVariant(this->m_categoryList.at(index.row())); // need to return name
    default:
        return QVariant();
    }
}

QHash<int, QByteArray> CategoryModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[CategoryRoles::CategoryPrefix] = "categoryPrefix";
    roles[CategoryRoles::Name] = "name";

    return roles;
}
