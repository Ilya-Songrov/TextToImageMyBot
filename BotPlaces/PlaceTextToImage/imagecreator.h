#pragma once

#include <QObject>
#include <QDir>

#ifdef QT_DEBUG
#include <QTextEdit>
#include <QTextBrowser>
#include <QWebEngineView>
#include <QWebEnginePage>
#include <QWebEngineSettings>
#endif

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
#ifdef QT_DEBUG
    static void testFunction();
#endif
    static QString addTemplateToText(const std::string &text, const QString &nameTemplate);

private:
    static const QString pathFolderTemp;
};

