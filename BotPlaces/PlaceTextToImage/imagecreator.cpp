#include "imagecreator.h"

const QString ImageCreator::pathFolderTemp = QDir::currentPath() + "/resources/tmp/";

ImageCreator::ImageCreator(QObject *parent) : QObject(parent)
{

}

#ifdef QT_DEBUG
void ImageCreator::testFunction(){
    //    const auto pix2 = ImageWorker::getPixmapFromText(FileWorker::readFile("../song_html2.html"));
    //    const auto pix2 = ImageWorker::getPixmapFromText(FileWorker::readFile("../text.html"));
    const auto textWithTemplate = ImageCreator::addTemplateToText(FileWorker::readFile("../song.txt").toStdString(), "holychords");
    const auto pix2 = ImageWorker::getPixmapFromText(textWithTemplate);

    const auto pathFile = "resources/tmp/some.png";
    //    pix2.save(pathFile, "png");
    //    FileWorker::writeFile(textWithTemplate.toUtf8(), "../text.html");

    static QLabel label;
    label.resize(pix2.size());
    label.setPixmap(pix2);
    //    label.show();

    static QTextEdit textEdit;
    textEdit.setHtml(textWithTemplate);
    textEdit.resize(textEdit.sizeHint());
    //    textEdit.show();

    static QTextBrowser textBrowser;
    textBrowser.resize(555, 555);
    textBrowser.setHtml(textWithTemplate);
    //    textBrowser.setSource(QUrl::fromLocalFile("../text.html"));
    //    textBrowser.resize(textBrowser.sizeHint());
    //    textBrowser.show();

    static QWebEngineView webEngineView;
//    webEngineView.setWindowFlags(Qt::FramelessWindowHint);
    webEngineView.setWindowFlags(webEngineView.windowFlags() & Qt::FramelessWindowHint);
    //    webEngineView.setSizePolicy(Qt::SizeMode)
    //        webEngineView.page()->settings()->setAttribute(QWebEngineSettings::ShowScrollBars, false);

    //    webEngineView.setAttribute(Qt::WA_DontShowOnScreen);
    //    webEngineView.setHtml(textWithTemplate);
    //    webEngineView.reload();
    //    const QSize size = webEngineView.page()->contentsSize().toSize();
    //    webEngineView.resize(size);
    //    webEngineView.show();
    //    QImage image;
    //    QPainter painter(&image);
    //        webEngineView.page()->view()->render(&painter);
    //    image.save(pathFile, "png");

    //        QPixmap pix = webEngineView.page()->view()->grab(QRect(QPoint(), webEngineView.size()));
    //        qDebug() << "pix" << pix.size() << webEngineView.size() << Qt::endl;
    //        pix.save(pathFile, "png");

    //    qDebug() << "SingleShot1" << webEngineView.page()->contentsSize().toSize() << Qt::endl;
    //    QTimer::singleShot(2000, [pathFile](){
    //        qDebug() << "SingleShot2" << webEngineView.page()->contentsSize().toSize() << Qt::endl;

    ////        QPixmap pix(34, 34);
    //    });
//    connect(&webEngineView, &QWebEngineView::loadFinished, [pathFile]() {
//        qDebug() << "loadFinishedloadFinishedloadFinished" << webEngineView.size() << webEngineView.sizeHint()
//                 << webEngineView.contentsRect() << webEngineView.page()->contentsSize().toSize() << Qt::endl;
//        //        webEngineView.resize(webEngineView.size());
//    });
    connect(webEngineView.page(), &QWebEnginePage::contentsSizeChanged, [pathFile](){
        qDebug() << "webEngineView.sizeHint" << webEngineView.page() << Qt::endl;
        //        webEngineView.show();
        qDebug() << "webEngineView.page()->contentsSize().toSize()" << webEngineView.page()->contentsSize().toSize() << Qt::endl;
//        static bool isResized = false;
//        if (!isResized) {
//            webEngineView.resize(webEngineView.page()->contentsSize().toSize());
//            QPixmap pix = webEngineView.grab(QRect(QPoint(), webEngineView.size()));
//            pix.save(pathFile, "png");
//            isResized = true;
//        }

        static int countResized = 0;
        if (countResized < 2) {
            qDebug() << "webEngineView.size1" << webEngineView.size() << Qt::endl;
            webEngineView.resize(webEngineView.page()->contentsSize().toSize());
            qDebug() << "webEngineView.size2" << webEngineView.size() << Qt::endl;
            QPixmap pix = webEngineView.grab(QRect(QPoint(0,0), webEngineView.size()));
//            QPixmap pix = webEngineView.grab(QRect(QPoint(), QSize(595, 1053)));
            pix.save(pathFile, "png");
            ++countResized;
        }
//        qFatal("Fatal");
    });
    webEngineView.setHtml(textWithTemplate);
    webEngineView.show();

//    connect(&webEngineView, &QWebEngineView::, [pathFile]() {
//        qDebug() << "loadFinishedloadFinishedloadFinished" << webEngineView.size() << webEngineView.sizeHint()
//                 << webEngineView.contentsRect() << webEngineView.page()->contentsSize().toSize() << Qt::endl;
//        //        webEngineView.resize(webEngineView.size());
//    });

//    webEngineView.resize(webEngineView.page()->contentsSize().toSize());
//    QPixmap pix = webEngineView.grab(QRect(QPoint(), webEngineView.size()));
//    pix.save(pathFile, "png");

    //    QTimer::singleShot(2220, [pathFile](){
    //        qDebug() << "singleShot2220" << Qt::endl;
    ////            const QSize size = webEngineView.page()->contentsSize().toSize();
    ////            webEngineView.resize(size);

    //    });

    //    webEngineView.resize(webEngineView.sizeHint());
    //    webEngineView.show();
}
#endif

void ImageCreator::initValues()
{
    if (!QDir().exists(pathFolderTemp)) {
        QDir().mkpath(pathFolderTemp);
    }
#ifdef QT_DEBUG
    testFunction();
#endif
}

InputFile::Ptr ImageCreator::getInputFile(const std::string &text, const QString &nameTemplate)
{
    static int number = 0;
    const auto pathFile = pathFolderTemp + QString::number(++number) + ".png";
    const auto textWithTemplate = addTemplateToText(text, nameTemplate);
    const auto pix = ImageWorker::getPixmapFromText(textWithTemplate);
    pix.save(pathFile, "png");
    const auto inputFile = InputFile::fromFile(pathFile.toStdString(), "");
#ifdef QT_NO_DEBUG
    if (!QFile::remove(pathFile)) {
        qWarning() << "Error, file was not remove" << pathFile << Qt::endl;
    }
#endif
    return inputFile;
}

QString ImageCreator::addTemplateToText(const std::string &text, const QString &nameTemplate)
{
    const OneTemplate oneTemplate = Templates::getTemplate(nameTemplate);
    QString result = oneTemplate.tagBegin + QString::fromStdString(text) + oneTemplate.tagEnd;
    for (const Replacer &replacer: oneTemplate.vecReplacers) {
        result.replace(replacer.word, replacer.tags);
    }
    return result;
}
