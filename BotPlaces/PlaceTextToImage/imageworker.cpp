#include "imageworker.h"

ImageWorker::ImageWorker()
{

}

QPixmap ImageWorker::getPixmapFromText(const QString &text)
{
#ifdef QT_DEBUG
    qDebug() << "Text" << text << Qt::endl;
    FileWorker::writeFile(text.toUtf8(), "../text.txt");
#endif
//    const QFont font("Calibri", 22);
//    const QFontMetrics fm(font);
//    QSize textSize = fm.size(Qt::TextExpandTabs, text);
//    textSize.setWidth(textSize.width() < 600 ? 600 : textSize.width());
//    textSize.setWidth(textSize.height() < 1280 ? 1280 : textSize.height());

    const auto id = QFontDatabase::addApplicationFont("/home/songrov/DeveloperRoot/Projects_Main/Ilya_Songrov/TextToImageMyBot/"
"TextToImageMyBot/Templates/holychords/RubrikNew-Light.otf");
    qDebug() << "id" << QFontDatabase::applicationFontFamilies(id) << Qt::endl;
    QLabel myLabel;
//    myLabel.setStyleSheet("QLabel { background-color : white; margin: 60px; }");
//    myLabel.setStyleSheet("QLabel { background-color : white; }");
//    myLabel.setFont(QFont());
    myLabel.setText(text);
    myLabel.resize(myLabel.sizeHint());
    QPixmap pix;
    pix = myLabel.grab(QRect(QPoint(), myLabel.size()));
    return pix;
}

QPixmap ImageWorker::getPixmapFromText(const QString &text, const QSize &size)
{
    Q_UNUSED(size)
    QPixmap pix;
    pix.fill(Qt::red);
    int fit = false;

    QLabel myLabel;
    QFont myFont = myLabel.font();
    while (!fit)
    {
        QFontMetrics fm( myFont );
        QRect bound = fm.boundingRect(0,0, myLabel.width(), myLabel.height(), Qt::TextWordWrap | Qt::AlignCenter, text);

        if (bound.width() <= myLabel.width() && bound.height() <= myLabel.height()){
            fit = true;
        }
        else {
            myFont.setPointSize(myFont.pointSize() - 1);
        }
    }
    myLabel.setFont(myFont);
    myLabel.setAlignment(Qt::AlignLeft);
    myLabel.setText(text);
    pix = myLabel.grab(QRect(QPoint(), myLabel.size()));
    return pix;
}
