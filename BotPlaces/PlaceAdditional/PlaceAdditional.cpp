#include "PlaceAdditional.h"

PlaceAdditional::PlaceAdditional(QObject *parent) : PlaceAbstract(parent)
{
    // TODO: new functiono - change_group_position
}

void PlaceAdditional::slotOnCommand(const Message::Ptr &message, const ChatActions &chatActions)
{
    // TODO: replace switch with if/else
    switch (chatActions.currentCommand) {
    case Content::Additional_Additional:
        onAdditional(message);
        break;
    case Content::MultiPlace_AnyMessage:
        onAdditional(message);
        break;
    default:
        PlaceAbstract::slotOnCommand(message, chatActions);
    }
}

void PlaceAdditional::slotOnCallbackQuery(const CallbackQuery::Ptr &callbackQuery, const ChatActions &chatActions)
{
    switch (chatActions.currentCommand) {
    case Content::Additional_ShowHistory:
        onShowHistory(callbackQuery);
        break;
    case Content::Additional_DeleteHistory:
        onDeleteHistory(callbackQuery);
        break;
    case Content::Additional_Developer:
        onDeveloper(callbackQuery);
        break;
    case Content::MultiPlace_AnyCallbackQuery:
        onAnyCallbackQuery(callbackQuery);
        break;
    default:
        PlaceAbstract::slotOnCallbackQuery(callbackQuery, chatActions);
    }
}

void PlaceAdditional::onAdditional(const Message::Ptr &message)
{
    static const auto keyboard = createOneColumnInlineKeyboardMarkup({Content::getCommandStr(Content::Additional_ShowHistory)
                                                                      , Content::getCommandStr(Content::Additional_DeleteHistory)
                                                                      , Content::getCommandStr(Content::Additional_Developer)
                                                                     });
    static const auto answer { QObject::tr("Select function:").toStdString() };
    bot->getApi().sendMessage(message->chat->id, answer, false, 0, keyboard, "Markdown");
}

void PlaceAdditional::onAnyMessage(const Message::Ptr &message)
{
    if (QString::fromStdString(message->text).toLower() == "ping") {
        sendMainMenuMessage(message->chat->id, "Pong!");
    }
}

void PlaceAdditional::onShowHistory(const CallbackQuery::Ptr &callbackQuery)
{

}

void PlaceAdditional::onDeleteHistory(const CallbackQuery::Ptr &callbackQuery)
{

}

void PlaceAdditional::onDeveloper(const CallbackQuery::Ptr &callbackQuery)
{
    const auto answer { QObject::tr("Hello! I'm Ilya. Write me if you have any questions (https://t.me/ilyaSongrov)").toStdString() };
    sendMainMenuMessage(callbackQuery->message->chat->id, answer);
}

void PlaceAdditional::onAnyCallbackQuery(const CallbackQuery::Ptr &callbackQuery)
{

}
