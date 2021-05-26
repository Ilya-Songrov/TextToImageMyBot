#include "imageworker.h"

ImageWorker::ImageWorker()
{

}

QPixmap ImageWorker::getPixmapFromText(const QString &text)
{
    const QFont font("Calibri", 12);
    const QFontMetrics fm(font);
    QSize textSize = fm.size(Qt::TextExpandTabs, text);
    textSize.setWidth(textSize.width() < 600 ? 600 : textSize.width());
    textSize.setWidth(textSize.height() < 1280 ? 1280 : textSize.height());

    QLabel myLabel;
//    myLabel.setStyleSheet("QLabel { background-color : white; color : blue; }");
    myLabel.setStyleSheet("QLabel { background-color : white;}");
    myLabel.setMargin(55);
//    myLabel.resize(textSize);
    myLabel.resize(QSize(textSize.width() + myLabel.margin() * 2, textSize.height() + myLabel.margin() * 2));
    myLabel.setFont(font);
    myLabel.setAlignment(Qt::AlignLeft);
    myLabel.setText(text);
//    pix = myLabel.grab(QRect(QPoint(), QSize(myLabel.width() + myLabel.margin(), myLabel.height() + myLabel.margin())));
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
