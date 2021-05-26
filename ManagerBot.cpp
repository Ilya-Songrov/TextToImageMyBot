#include "ManagerBot.h"


ManagerBot::ManagerBot(const QString token, QObject *parent) : QObject(parent)
  , appTranslator(":/translationFiles/NoteBot_UA.qm")
  , mapAllChats(new QMap<std::uint64_t, ChatActions>())
{
    Templates::initValues();
    ImageCreator::initValues();
    Content::initContent();
    initGlobalData(token.isEmpty() ? getTokenFromFile() : token);
    PlaceAbstract::initMapAllChats(mapAllChats);

    placeStart          = new PlaceStart    (this);
    placeTextToImage    = new PlaceTextToImage    (this);
    placeAdditional     = new PlaceAdditional   (this);
    placeBot            = placeTextToImage;
    setSettings();
}

void ManagerBot::startBot()
{
    //    signal(SIGINT, [](int s) {
    //        printf("SIGINT got\n");
    //        exit(0);
    //    });

    qDebug("Token: %s\n", bot->getToken().c_str());
    QtConcurrent::run([](){
        try {
            qDebug("Bot username: %s\n", bot->getApi().getMe()->username.c_str());
            bot->getApi().deleteWebhook();

            TgLongPoll longPoll(*bot.get());
            while (true) {
                qDebug("Long poll started\n");
                longPoll.start();
            }
        } catch (std::exception& e) {
            qDebug("error: %s\n", e.what());
        }
    });
}

void ManagerBot::setSettings()
{
    bot->getEvents().onAnyMessage(std::bind(&ManagerBot::anyMessageWasWrite, this, std::placeholders::_1));
    bot->getEvents().onCallbackQuery(std::bind(&ManagerBot::callbackQueryWasWrite, this, std::placeholders::_1));

    bot->getEvents().onInlineQuery([](const InlineQuery::Ptr){ qDebug() << "onInlineQuery" << Qt::endl; });
    bot->getEvents().onChosenInlineResult([](const ChosenInlineResult::Ptr){ qDebug() << "onChosenInlineResult" << Qt::endl; });
    //    bot->getEvents().onCallbackQuery([](const CallbackQuery::Ptr &callbackQuery){ qDebug() << "onCallbackQuery" << callbackQuery->data.c_str() << Qt::endl; });
}

void ManagerBot::anyMessageWasWrite(const Message::Ptr message)
{
    const auto chatActions = getChatActions(message->chat->id, message->text);
    printChatActions(QString(__FUNCTION__), chatActions, message->text);
    mapAllChats->insert(message->chat->id, chatActions);
    changeObjPtrPlaceBot(chatActions.currentPlace);
    placeBot->slotOnCommand(message, chatActions);
}

void ManagerBot::callbackQueryWasWrite(const CallbackQuery::Ptr callbackQuery)
{
    const auto chatActions = getChatActions(callbackQuery->message->chat->id, callbackQuery->data);
    printChatActions(QString(__FUNCTION__), chatActions, callbackQuery->message->text);
    mapAllChats->insert(callbackQuery->message->chat->id, chatActions);
    changeObjPtrPlaceBot(chatActions.currentPlace);
    placeBot->slotOnCallbackQuery(callbackQuery, chatActions);
}

ChatActions ManagerBot::getChatActions(const int64_t chat_id, const std::string &currentText)
{
    const Content::PlaceCommand currentPlaceCommand = Content::getPlaceCommand(currentText);
    ChatActions chatActions =     mapAllChats->value(chat_id);
    chatActions.lastPlace      = chatActions.currentPlace;
    chatActions.lastCommand    = chatActions.currentCommand;
    chatActions.currentPlace   = currentPlaceCommand.place;
    chatActions.currentCommand = currentPlaceCommand.command;
    return chatActions;
}

void ManagerBot::changeObjPtrPlaceBot(const Content::Place place)
{
    if (place == Content::Place::Start) {
        placeBot = placeStart;
    }
    else if (place == Content::Place::TextToImage) {
        placeBot = placeTextToImage;
    }
    else if (place == Content::Place::Additional) {
        placeBot = placeAdditional;
    }
    else {
        placeBot = placeTextToImage;
    }
}

QString ManagerBot::getTokenFromFile()
{
    const QJsonDocument doc = FileWorker::readFileJson("../config.json");
    const QJsonObject obj = doc.object();
    return obj.value("token").toString();
}

void ManagerBot::printChatActions(const QString &header, const ChatActions &chatActions, const std::string &messageText)
{
    static const QChar placeholder { '-' };
    static const int lenghtSymbols = 48;
    static const int justified = lenghtSymbols / 2 + header.size() / 2;
    const QString frameHeader = QString(header).leftJustified(justified, '-').rightJustified(lenghtSymbols, placeholder);

    qDebug() << frameHeader << Qt::endl;
    qDebug() << "currentPlace   :" << chatActions.currentPlace     ;
    qDebug() << "currentCommand :" << chatActions.currentCommand   ;
    qDebug() << "lastPlace      :" << chatActions.lastPlace        ;
    qDebug() << "lastCommand    :" << chatActions.lastCommand      ;
    qDebug() << "lastGroup      :" << chatActions.lastGroup        ;
    qDebug() << "messageText    :" << messageText.c_str()       ;
    qDebug() << Qt::endl << frameHeader << Qt::endl;
}
