/**************************************************************************
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3 as published by the Free Software
** Foundation with exceptions as appearing in the file LICENSE.GPL3
** included in the packaging of this file. Please review the following
** information to ensure the GNU General Public License requirements will
** be met: https://www.gnu.org/licenses/.
**
**************************************************************************/

#include "templates.h"

#ifdef QT_DEBUG
QString Templates::pathFolderTemplates = QFileInfo("../").absolutePath() + "/TextToImageMyBot/Templates";
QString Templates::fileTemplates = QFileInfo("../").absolutePath() + "/TextToImageMyBot/Templates/templates.json";
#else
QString Templates::pathFolderTemplates = QFileInfo("../").absolutePath() + "/Resources/Templates";
QString Templates::fileTemplates = QFileInfo("../").absolutePath() + "/Resources/Templates/templates.json";
#endif
QScopedPointer<QVector<OneTemplate> > Templates::vecTemplates(new QVector<OneTemplate>);

Templates::Templates()
{

}

#ifdef QT_DEBUG
void createDefaultTemplates()
{
    OneTemplate oneTemplate;
    oneTemplate.name        = "holychords";
    oneTemplate.tagBegin    = "<pre style=\"font-family:'Rubrik New'; font-size: 42px; position: relative;\">";
    oneTemplate.tagEnd      = "</pre>";
#ifdef QT_DEBUG
//    oneTemplate.tagBegin    = "<html><body style='background-color:white';><pre style=\"font-family:'Rubrik New'; font-size: 12px; position: relative;\">";
    oneTemplate.tagBegin    = "<!DOCTYPE html>"
"<html>"
"<meta charset='utf-8'>"
"<body>"
"<style>"
"  body {"
"   margin: 90px;"
"   background: red;"
"  }"
".videlit_line {"
"    color: #51ab6c;"
"    padding: 3px 0 3px 1.5rem;"
"    background: rgb(241, 245, 241);"
"    text-transform: uppercase;"
"    min-width: 30%;"
"    display: inline-block;"
"    margin-left: -1.5rem;"
"}"
"</style>"
"<pre style=font-family:'Rubrik New'; font-size: 12px; position: relative;>";
    oneTemplate.tagEnd      = "</pre></div></body></html>";
#endif
    Replacer replacer;
    replacer.word = "1 куплет:";
    replacer.tags = "<b style='color: #51ab6c; padding: 9px 0 9px 1.5rem; background: \"#f1f5f1\"; text-transform: uppercase; min-width: 50%; display: inline-block; margin-left: -1.5rem;'>1 куплет:</b>";
#ifdef QT_DEBUG
    replacer.tags = "<b class=videlit_line>1 куплет:</b>";
#endif
    oneTemplate.vecReplacers.append(replacer);
    replacer.word = "2 куплет:";
    replacer.tags = "<b style='color: #51ab6c; padding: 9px 0 9px 1.5rem; background: \"#f1f5f1\"; text-transform: uppercase; min-width: 50%; display: inline-block; margin-left: -1.5rem;'>2 куплет:</b>";
    oneTemplate.vecReplacers.append(replacer);
    replacer.word = "3 куплет:";
    replacer.tags = "<b style='color: #51ab6c; padding: 9px 0 9px 1.5rem; background: \"#f1f5f1\"; text-transform: uppercase; min-width: 50%; display: inline-block; margin-left: -1.5rem;'>3 куплет:</b>";
    oneTemplate.vecReplacers.append(replacer);
    replacer.word = "4 куплет:";
    replacer.tags = "<b style='color: #51ab6c; padding: 9px 0 9px 1.5rem; background: \"#f1f5f1\"; text-transform: uppercase; min-width: 50%; display: inline-block; margin-left: -1.5rem;'>4 куплет:</b>";
    oneTemplate.vecReplacers.append(replacer);
    replacer.word = "Приспів:";
    replacer.tags = "<b style='color: #51ab6c; padding: 9px 0 9px 1.5rem; background: \"#f1f5f1\"; text-transform: uppercase; min-width: 50%; display: inline-block; margin-left: -1.5rem;'>Приспів:</b>";
    oneTemplate.vecReplacers.append(replacer);
    replacer.word = "Припев:";
    replacer.tags = "<b style='color: #51ab6c; padding: 9px 0 9px 1.5rem; background: \"#f1f5f1\"; text-transform: uppercase; min-width: 50%; display: inline-block; margin-left: -1.5rem;'>Припев:</b>";
    oneTemplate.vecReplacers.append(replacer);
    replacer.word = "Предприпев:";
    replacer.tags = "<b style='color: #51ab6c; padding: 9px 0 9px 1.5rem; background: \"#f1f5f1\"; text-transform: uppercase; min-width: 50%; display: inline-block; margin-left: -1.5rem;'>Предприпев:</b>";
    oneTemplate.vecReplacers.append(replacer);

    Templates::addNewTemplate(oneTemplate);
}
#endif

void Templates::initValues()
{
#ifdef QT_DEBUG
    createDefaultTemplates();
#endif
    createFolders();
    loadAllTemplates();
}

void Templates::loadAllTemplates()
{
    const QJsonDocument doc = FileWorker::readFileJson(fileTemplates);
    const QJsonArray arrRoot = doc.array();
    for (const auto &value: arrRoot) {
        const QJsonObject objOneTemplate = value.toObject();
        const OneTemplate oneTemplate = createOneTemplateFromObj(objOneTemplate);
        vecTemplates->append(oneTemplate);
    }
}

OneTemplate Templates::getTemplate(const QString &nameTemplate)
{
    for (const OneTemplate &one: qAsConst(*vecTemplates)) {
        if (one.name == nameTemplate) {
            return one;
        }
    }
    return {};
}

void Templates::addNewTemplate(const OneTemplate &oneTemplate)
{
    const auto objOneTemplate = createObjFromOneTemplate(oneTemplate);
    const auto doc = FileWorker::readFileJson(fileTemplates);
    QJsonArray arr = doc.array();
    updateTemplateInArray(&arr, objOneTemplate);
    FileWorker::writeFileJson(QJsonDocument(arr), fileTemplates);
}

void Templates::createFolders()
{
    if (!QDir().exists(pathFolderTemplates) && !QDir().mkpath(pathFolderTemplates)) {
        qDebug() << "Can not create folder: %1" << pathFolderTemplates << Qt::endl;
    }
}

void Templates::updateTemplateInArray(QJsonArray *arr, const QJsonObject &objOneTemplate)
{
    for (QJsonValueRef valueRef: *arr) {
        const QJsonObject obj = valueRef.toObject();
        const QString nameOld = obj.value("name").toString();
        const QString nameNew = objOneTemplate.value("name").toString();
        if (nameOld == nameNew) {
            valueRef = objOneTemplate;
            return;;
        }
    }
    arr->append(objOneTemplate);
}

OneTemplate Templates::createOneTemplateFromObj(const QJsonObject &objOneTemplate)
{
    OneTemplate oneTemplate;
    oneTemplate.name        = objOneTemplate.value("name").toString();
    oneTemplate.tagBegin    = objOneTemplate.value("tagBegin").toString();
    oneTemplate.tagEnd      = objOneTemplate.value("tagEnd").toString();
    const QJsonObject objReplacers = objOneTemplate.value("replacers").toObject();
    const auto keys = objReplacers.keys();
    for (const auto &key: keys) {
        Replacer replacer;
        replacer.word = key;
        replacer.tags = objReplacers.value(key).toString();
        oneTemplate.vecReplacers.append(replacer);
    }
    return oneTemplate;
}

QJsonObject Templates::createObjFromOneTemplate(const OneTemplate &oneTemplate)
{
    QJsonObject objOneTemplate;
    objOneTemplate.insert("name",       oneTemplate.name);
    objOneTemplate.insert("tagBegin",   oneTemplate.tagBegin);
    objOneTemplate.insert("tagEnd",     oneTemplate.tagEnd);
    QJsonObject objReplacers;
    for (const Replacer &replacer: oneTemplate.vecReplacers) {
        objReplacers.insert(replacer.word, replacer.tags);
    }
    objOneTemplate.insert("replacers", objReplacers);
    return objOneTemplate;
}
