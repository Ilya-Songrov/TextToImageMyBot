#pragma once

#include <QObject>

#include "PlaceAbstract.h"
#include "imagecreator.h"

class PlaceTextToImage : public PlaceAbstract
{
public:
    explicit PlaceTextToImage(QObject *parent = nullptr);

    virtual void slotOnCommand(const Message::Ptr &message, const ChatActions &chatActions) override;
    virtual void slotOnCallbackQuery(const CallbackQuery::Ptr &callbackQuery, const ChatActions &chatActions) override;

private:
    void onAnyMessage(const Message::Ptr &message);
    void onAnyCallbackQuery(const CallbackQuery::Ptr &callbackQuery);

};

