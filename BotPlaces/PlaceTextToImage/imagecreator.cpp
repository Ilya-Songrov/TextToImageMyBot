#include "imagecreator.h"

#include "imageworker.h"

#include <QDir>

const QString ImageCreator::pathFolderTemp = QDir::currentPath() + "/resources/tmp/";

ImageCreator::ImageCreator(QObject *parent) : QObject(parent)
{

}

void ImageCreator::initValues()
{
    if (!QDir().exists(pathFolderTemp)) {
        QDir().mkpath(pathFolderTemp);
    }
#ifdef QT_DEBUG
    getInputFile("test");
#endif
}

InputFile::Ptr ImageCreator::getInputFile(const std::string &text)
{
    static int numFile = 0;
    ++numFile;
    const auto pix = ImageWorker::getPixmapFromText(QString::fromStdString(text));
    const auto pathFile = pathFolderTemp + QString::number(numFile) + ".png";
    pix.save(pathFile, "png");
    auto inputFile = InputFile::fromFile(pathFile.toStdString(), "");
    if (!QFile::remove(pathFile)) {
        qWarning() << "Error, file was not remove" << pathFile << Qt::endl;
    }
    return inputFile;
}
