#pragma once

#include <QObject>
#include <QDebug>
#include <QSize>
#include <QFile>
#include <QFileInfo>
#include <QImage>
#include <QPainter>
#include <QTimer>

class ImageWorker
{
    enum MaxValues{
        MaxSizeWidth    = 256,
        MaxSizeHeight   = MaxSizeWidth,
        MaxWidth        = 560,
    };

public:
    ImageWorker();

    static QPixmap getPixmapFromText(const QString &text);
    static QPixmap getPixmapFromText(const QString &text, const QSize &size);
};
