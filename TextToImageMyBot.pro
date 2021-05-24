QT      += gui
QT      += widgets
QT      += sql
QT      += concurrent

CONFIG += c++14 console
CONFIG -= app_bundle

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Adjutants/AppTranslator.cpp \
    Adjutants/FileWorker.cpp \
    Anomalies/Errors.cpp \
    Anomalies/ExceptionHandler.cpp \
    BotPlaces/PlaceAbstract.cpp \
    BotPlaces/PlaceAdditional/PlaceAdditional.cpp \
    BotPlaces/PlaceTextToImage/PlaceTextToImage.cpp \
    BotPlaces/PlaceStart/placestart.cpp \
    BotPlaces/PlaceTextToImage/imagecreator.cpp \
    BotPlaces/PlaceTextToImage/imageworker.cpp \
    Content/Content.cpp \
    Database/DatabaseConnector.cpp \
    Database/managerdatabase.cpp \
    GlobalData/GlobalData.cpp \
    ManagerBot.cpp \
    main.cpp \

HEADERS += \
    Adjutants/AppTranslator.h \
    Adjutants/FileWorker.h \
    Anomalies/ApplicationNotify.h \
    Anomalies/Errors.h \
    Anomalies/ExceptionHandler.h \
    BotPlaces/PlaceAbstract.h \
    BotPlaces/PlaceAdditional/PlaceAdditional.h \
    BotPlaces/PlaceTextToImage/PlaceTextToImage.h \
    BotPlaces/PlaceStart/placestart.h \
    BotPlaces/PlaceTextToImage/imagecreator.h \
    BotPlaces/PlaceTextToImage/imageworker.h \
    Content/ChatActions.h \
    Content/Content.h \
    Content/chatsettings.h \
    Database/DatabaseConnector.h \
    Database/managerdatabase.h \
    GlobalData/GlobalData.h \
    ManagerBot.h \
    tgbot/include/tgbot/tgbot.h

INCLUDEPATH += \
    tgbot/include \
    Adjutants \
    Anomalies \
    Database \
    Content \
    BotPlaces \


unix:!macx: LIBS += -L$$PWD/tgbot -lTgBot
INCLUDEPATH += $$PWD/tgbot
DEPENDPATH  += $$PWD/tgbot
unix:!macx: PRE_TARGETDEPS += $$PWD/tgbot/libTgBot.a

#-lTgBot -lboost_system -lssl -lcrypto -lpthread
unix:!macx: LIBS += -lboost_system
unix:!macx: LIBS += -lssl
unix:!macx: LIBS += -lcrypto
unix:!macx: LIBS += -lpthread

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    Resources/translationFiles.qrc

TRANSLATIONS += \
#    Resources/translationFiles/NoteBot_UA.ts \


### ApplicationLogLib ###
HEADERS += \
    ApplicationLogLib/ApplicationLogLib.h \
    ApplicationLogLib/ApplicationLogLib_global.h \

unix:!macx: LIBS += -L$$PWD/ApplicationLogLib/ -lApplicationLogLib
INCLUDEPATH += $$PWD/ApplicationLogLib
DEPENDPATH  += $$PWD/ApplicationLogLib
unix:!macx: PRE_TARGETDEPS += $$PWD/ApplicationLogLib/libApplicationLogLib.so
#QMAKE_LFLAGS += -Wl,-rpath,"'\$$ORIGIN'"   # OR
QMAKE_RPATHDIR += ":'\$$ORIGIN'"            # OR
### ApplicationLogLib ###

### cqtdeployer ###
CONFIG(release, debug | release) {
QMAKE_POST_LINK=/bin/bash -c \"cqtdeployer -bin $${OUT_PWD}/$${TARGET} -targetDir DeployKit_$${TARGET} -qmake $${QMAKE_QMAKE} -libDir $${PWD} \
                               -recursiveDepth 10 -qmlDir $${PWD} force-clear ; \"
}
### cqtdeployer ###
