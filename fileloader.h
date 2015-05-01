#ifndef FILELOADER_H
#define FILELOADER_H

#include <QObject>
#include <QStringList>
#include <QSet>

#include "imagemodel.h"
#include "categorymodel.h"

class FileLoader : public QObject
{
    Q_OBJECT

    Q_PROPERTY(CategoryModel* categoryModel READ categoryModel NOTIFY categoryModelChanged)
public:
    explicit FileLoader(QObject *parent = 0);
    ~FileLoader();

    Q_INVOKABLE void loadImageList(QString path);

    CategoryModel *categoryModel() const;
    Q_INVOKABLE ImageModel *imageModel(QString categoryPrefix) const;

    Q_INVOKABLE void selectImage(QString path);
    Q_INVOKABLE void unselectImage(QString path);

signals:
    void categoryModelChanged();

public slots:
    void hideItems(bool hide);

private:
    QStringList m_itemsList;
    QSet<QString> m_categories;
    QSet<QString> m_selectedItems;
    bool m_hide;
    QString m_lastPath;
};

#endif // FILELOADER_H
