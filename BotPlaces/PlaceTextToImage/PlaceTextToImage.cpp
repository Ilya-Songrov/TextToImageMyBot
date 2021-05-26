#include "PlaceTextToImage.h"

PlaceTextToImage::PlaceTextToImage(QObject *parent) : PlaceAbstract(parent)
{
#ifdef QT_DEBUG
    createDefauilTemplates();
#endif
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
    // TODO: get template from db
    bot.get()->getApi().sendPhoto(chat_id, ImageCreator::getInputFile(message->text, "holychords"));
}

void PlaceTextToImage::onAnyCallbackQuery(const CallbackQuery::Ptr &callbackQuery)
{

}

#ifdef QT_DEBUG
void PlaceTextToImage::createDefauilTemplates()
{
    // TODO: move to another class
    OneTemplate oneTemplate;
    oneTemplate.name = "holychords";
    Replacer replacer;
    replacer.word = "1 куплет:";
    replacer.tags = "<b style='color: #51ab6c; padding: 3px 0 3px 1.5rem; background: \"rgb(241, 245, 241)\"; text-transform: uppercase; min-width: 50%; display: inline-block; margin-left: -1.5rem;'>1 куплет:</b>";
    oneTemplate.vecReplacers.append(replacer);
    replacer.word = "2 куплет:";
    replacer.tags = "<b style='color: #51ab6c; padding: 3px 0 3px 1.5rem; background: \"rgb(241, 245, 241)\"; text-transform: uppercase; min-width: 50%; display: inline-block; margin-left: -1.5rem;'>2 куплет:</b>";
    oneTemplate.vecReplacers.append(replacer);
    replacer.word = "3 куплет:";
    replacer.tags = "<b style='color: #51ab6c; padding: 3px 0 3px 1.5rem; background: \"rgb(241, 245, 241)\"; text-transform: uppercase; min-width: 50%; display: inline-block; margin-left: -1.5rem;'>3 куплет:</b>";
    oneTemplate.vecReplacers.append(replacer);
    replacer.word = "4 куплет:";
    replacer.tags = "<b style='color: #51ab6c; padding: 3px 0 3px 1.5rem; background: \"rgb(241, 245, 241)\"; text-transform: uppercase; min-width: 50%; display: inline-block; margin-left: -1.5rem;'>4 куплет:</b>";
    oneTemplate.vecReplacers.append(replacer);
    replacer.word = "Приспів:";
    replacer.tags = "<b style='color: #51ab6c; padding: 3px 0 3px 1.5rem; background: \"rgb(241, 245, 241)\"; text-transform: uppercase; min-width: 50%; display: inline-block; margin-left: -1.5rem;'>Приспів:</b>";
    oneTemplate.vecReplacers.append(replacer);
    replacer.word = "Припев:";
    replacer.tags = "<b style='color: #51ab6c; padding: 3px 0 3px 1.5rem; background: \"rgb(241, 245, 241)\"; text-transform: uppercase; min-width: 50%; display: inline-block; margin-left: -1.5rem;'>Припев:</b>";
    oneTemplate.vecReplacers.append(replacer);
    replacer.word = "Предприпев:";
    replacer.tags = "<b style='color: #51ab6c; padding: 3px 0 3px 1.5rem; background: \"rgb(241, 245, 241)\"; text-transform: uppercase; min-width: 50%; display: inline-block; margin-left: -1.5rem;'>Предприпев:</b>";
    oneTemplate.vecReplacers.append(replacer);

    Templates::addNewTemplate(oneTemplate);
}
#endif

