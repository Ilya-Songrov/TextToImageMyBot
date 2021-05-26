#include "imagecreator.h"

const QString ImageCreator::pathFolderTemp = QDir::currentPath() + "/resources/tmp/";

ImageCreator::ImageCreator(QObject *parent) : QObject(parent)
{

}

void ImageCreator::initValues()
{
    if (!QDir().exists(pathFolderTemp)) {
        QDir().mkpath(pathFolderTemp);
    }
#ifdef QT_DEBUG
//    getInputFile("test");
#endif
}

#ifdef QT_DEBUG
void testFunction(){
    const QString song {
        "<pre>"
        "<style>"
        "        .videlit_line {"
        "            color: #51ab6c;"
        "            padding: 3px 0 3px 1.5rem;"
        "            background: rgb(241, 245, 241);"
        "            background: lightgreen;"
        "            text-transform: uppercase;"
        "            min-width: 50%;"
        "            display: inline-block;"
        "            margin-left: -1.5rem;"
        "        }"
        "</style>"
        "<b class='videlit_line'>1 куплет:</b>"
        "\nНет ценнее, Иисус, Тебя"
        "\nДрагоценность, Ты, моя"
        "\nПотрачу жизнь я на Тебя"
        "\nВедь это все, что я могу Тебе отдать"
        "\n\n"
        "\nПредприпев:"
        "\nДаже если не узнает никто никогда,"
        "\nЧего мне это стоит , чтоб выбрать Тебя"
        "\nВсе равно я буду выбирать Тебя"
        "\nДаже если заберут все, что есть у меня."
        "\n\n"
        "\nПрипев:"
        "\nОно того стоит, оно того стоит"
        "\nОно того стоит, положить всю жизнь"
        "\nОно того стоит, оно того стоит"
        "\nОно того стоит..."
        "\n\n"
        "\n2 куплет:"
        "\nРазолью все масло на ноги Твои"
        "\nЛюди скажут: “Пустая трата сил"
        "\nСвоё сердце не дал, Ты, по частям"
        "\nИ своё я только целое отдам"
        "\n\n"
        "\nПредприпев:"
        "\nДаже если тело убьют мое"
        "\nЯ не променяю Тебя ни на что"
        "\n\n"
        "\nПрипев:"
        "\nОно того стоит, оно того стоит"
        "\nОно того стоит, положить всю жизнь"
        "\nОно того стоит, оно того стоит"
        "\nОно того стоит..."
        "\n\n"
        "\nОно того стоит, оно того стоит"
        "\nОно того стоит, потратить жизнь на Тебя"
        "\nОно того стоит, да, Ты того стоишь"
        "\nОно того стоит..."
        "</pre>"
    };
    //    const auto pix2 = ImageWorker::getPixmapFromText("<strong>Hello</strong><font color=red>Wanderson !");
//    const auto pix2 = ImageWorker::getPixmapFromText(song);
    const auto pix2 = ImageWorker::getPixmapFromText(FileWorker::readFile("../song_html.html"));
    static QLabel label;
    label.resize(pix2.size());
    label.setPixmap(pix2);
    label.show();
}
#endif

InputFile::Ptr ImageCreator::getInputFile(const std::string &text, const QString &nameTemplate)
{
#ifdef QT_DEBUG
//    testFunction();
//    return {};
#endif
    static int number = 0;
    const auto pathFile = pathFolderTemp + QString::number(++number) + ".png";
    const auto textWithTemplate = addTemplateToText(text, nameTemplate);
    const auto pix = ImageWorker::getPixmapFromText(textWithTemplate);
    pix.save(pathFile, "png");
    const auto inputFile = InputFile::fromFile(pathFile.toStdString(), "");
    if (!QFile::remove(pathFile)) {
        qWarning() << "Error, file was not remove" << pathFile << Qt::endl;
    }
    return inputFile;
}

QString ImageCreator::addTemplateToText(const std::string &text, const QString &nameTemplate)
{
    const OneTemplate oneTemplate = Templates::getTemplate(nameTemplate);
    QString result = "<pre>" + QString::fromStdString(text) + "</pre>";
    for (const Replacer &replacer: oneTemplate.vecReplacers) {
        result.replace(replacer.word, replacer.tags);
    }
    return result;
}
