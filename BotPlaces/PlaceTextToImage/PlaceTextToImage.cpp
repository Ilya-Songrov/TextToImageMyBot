#include "PlaceTextToImage.h"

PlaceTextToImage::PlaceTextToImage(QObject *parent) : PlaceAbstract(parent)
{

}

void PlaceTextToImage::slotOnCommand(const Message::Ptr &message, const ChatActions &chatActions)
{
    if (chatActions.currentCommand == Content::MultiPlace_AnyMessage) {
        onAnyMessage(message);
    }
    else{
        PlaceAbstract::slotOnCommand(message, chatActions);
    }
}

void PlaceTextToImage::slotOnCallbackQuery(const CallbackQuery::Ptr &callbackQuery, const ChatActions &chatActions)
{

}


void PlaceTextToImage::onAnyMessage(const Message::Ptr &message)
{
    const auto chat_id = message->chat->id;
    sendMainMenuMessage(chat_id, "test");
//    bot.get()->getApi().sendPhoto(chat_id, InputFile::fromFile("/home/songrov/Downloads/glorification.jpg", ""));
    bot.get()->getApi().sendPhoto(chat_id, ImageCreator::getInputFile(message->text));
}

void PlaceTextToImage::onAnyCallbackQuery(const CallbackQuery::Ptr &callbackQuery)
{

}

