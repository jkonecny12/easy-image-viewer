#ifndef FILELOADER_H
#define FILELOADER_H

#include <QObject>
#include <QStringList>
#include <QSet>

#include "imagemodel.h"

class FileLoader : public QObject
{
    Q_OBJECT

    Q_PROPERTY(ImageModel* imageModel READ imageModel NOTIFY imageModelChanged)
    Q_PROPERTY(QString rootPath READ rootPath WRITE setRootPath NOTIFY rootPathChanged)
    Q_PROPERTY(QString folderName READ folderName WRITE setFolderName NOTIFY folderNameChanged)
public:
    explicit FileLoader(QObject *parent = 0);
    ~FileLoader();

    Q_INVOKABLE void loadImageList();

    ImageModel *imageModel();

    Q_INVOKABLE void selectImage(QString path);
    Q_INVOKABLE void unselectImage(QString path);

    Q_INVOKABLE QStringList selectedItems() const;

    QString rootPath() const;
    void setRootPath(QString path);

    QString folderName() const;
    void setFolderName(QString name);

signals:
    void imageModelChanged();
    void rootPathChanged();
    void folderNameChanged();

public slots:
    void hideItems(bool hide);

    void saveSelectedItems(QString user);
    bool loadSelectedItems(QString user);

private:
    QString reducePath(const QString path) const;
    QString expandPath(const QString path) const;

private:
    QStringList m_itemsList;
    QSet<QString> m_selectedItems;
    QSet<QString> m_visibleSelectedItems;
    bool m_hide;
    QString m_rootPath;
    QString m_folderName;
    ImageModel *m_activeModel;
};

#endif // FILELOADER_H
