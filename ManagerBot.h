#pragma once

#include <QObject>
#include <QString>
#include <QVariant>
#include <QtConcurrent>

#include "ApplicationLogLib/ApplicationLogLib.h"
#include "Adjutants/AppTranslator.h"
#include "FileWorker.h"
#include "GlobalData/GlobalData.h"
#include "Content/Content.h"
#include "Content/ChatActions.h"
#include "BotPlaces/PlaceStart/placestart.h"
#include "BotPlaces/PlaceTextToImage/PlaceTextToImage.h"
#include "BotPlaces/PlaceAdditional/PlaceAdditional.h"

#include <tgbot/tgbot.h>
using namespace TgBot;

class ManagerBot : public QObject
{
    Q_OBJECT

public:
    explicit ManagerBot(const QString token = QString(), QObject *parent = nullptr);

    void startBot();

private:
    void setSettings();
    void anyMessageWasWrite(const Message::Ptr message);
    void callbackQueryWasWrite(const CallbackQuery::Ptr callbackQuery);

    ChatActions getChatActions(const std::int64_t chat_id, const std::string &currentText);
    void changeObjPtrPlaceBot(const Content::Place place);
    QString getTokenFromFile();

    void printChatActions(const QString &header, const ChatActions &chatActions, const std::string &messageText);

private:
    ApplicationLogLib applicationLogLib;
    AppTranslator appTranslator;
    PlaceStart          *placeStart     ;
    PlaceTextToImage          *placeTextToImage     ;
    PlaceAdditional     *placeAdditional;
    PlaceAbstract       *placeBot       ;
    std::shared_ptr<QMap<std::uint64_t, ChatActions> > mapAllChats;
};

