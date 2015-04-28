#include "fileloader.h"

FileLoader::FileLoader(QObject *parent) : QObject(parent)
{

}

FileLoader::~FileLoader()
{

}

void FileLoader::loadImageList(const QString path)
{
    // TODO: load images for category

    emit imageModelChanged();
}

ImageModel *FileLoader::imageModel() const
{
    return new ImageModel("test path", "test name");
}
