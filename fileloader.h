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

    ImageModel *imageModel() const;

    Q_INVOKABLE void selectImage(QString path);
    Q_INVOKABLE void unselectImage(QString path);

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
    void loadSelectedItems(QString user);

private:
    QString reducePath(const QString path);
    QString expandPath(const QString path);

private:
    QStringList m_itemsList;
    QSet<QString> m_selectedItems;
    bool m_hide;
    QString m_rootPath;
    QString m_folderName;
};

#endif // FILELOADER_H
