#pragma once

#include <QObject>

#include <tgbot/tgbot.h>
using namespace TgBot;

class ImageCreator : public QObject
{
    Q_OBJECT
public:
    explicit ImageCreator(QObject *parent = nullptr);

    static void initValues();

    static InputFile::Ptr getInputFile(const std::string &text);

private:
    static QImage createImageFromText(const std::string &text);

private:
    static const QString pathFolderTemp;
};

