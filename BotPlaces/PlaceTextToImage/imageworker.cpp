#include "imageworker.h"

#include <QLabel>

ImageWorker::ImageWorker()
{

}

QPixmap ImageWorker::getPixmapFromText(const QString &text)
{
    QPixmap pix;

    QFont font("Ubuntu Mono", 12);
    QFontMetrics fm(font);
    QSize textSize = fm.size(Qt::TextExpandTabs, text);

    QLabel myLabel;
    myLabel.resize(textSize);
    myLabel.setFont(font);
    myLabel.setAlignment(Qt::AlignLeft);
    myLabel.setText(text);
    pix = myLabel.grab(QRect(QPoint(), myLabel.size()));


#ifdef QT_DEBUG
    myLabel.setText("<strong>Hello</strong><font color=red>Wanderson !");
    pix.fill(Qt::red);
    pix = myLabel.grab(QRect(QPoint(), myLabel.size()));
    QLabel *label = new QLabel;
    label->resize(QSize(222, 222));
    label->setPixmap(pix);
    label->show();
#endif
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
