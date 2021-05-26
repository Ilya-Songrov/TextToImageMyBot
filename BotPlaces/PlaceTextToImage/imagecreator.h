#pragma once

#include <QObject>
#include <QDir>

#include "FileWorker.h"
#include "imageworker.h"
#include "templates.h"

#include <tgbot/tgbot.h>
using namespace TgBot;

class ImageCreator : public QObject
{
    Q_OBJECT
public:
    explicit ImageCreator(QObject *parent = nullptr);

    static void initValues();

    static InputFile::Ptr getInputFile(const std::string &text, const QString &nameTemplate);

private:
    static QString addTemplateToText(const std::string &text, const QString &nameTemplate);

private:
    static const QString pathFolderTemp;
};

