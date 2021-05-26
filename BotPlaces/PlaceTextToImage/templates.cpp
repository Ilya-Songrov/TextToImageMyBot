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

void Templates::initValues()
{
    createFolders();
    loadAllTemplates();
}

void Templates::loadAllTemplates()
{
    const QJsonDocument doc = FileWorker::readFileJson(fileTemplates);
    const QJsonObject objRoot = doc.object();
    const QStringList keys = objRoot.keys();
    for (const auto &key: keys) {
        const QJsonObject objOneTemplate = objRoot.value(key).toObject();
        const OneTemplate oneTemplate = createOneTemplateFromObj(objOneTemplate, key);
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
    const auto doc = FileWorker::readFileJson(fileTemplates);
    QJsonObject obj = doc.object();
    obj.insert(oneTemplate.name, createObjFromOneTemplate(oneTemplate));
    FileWorker::writeFileJson(QJsonDocument(obj), fileTemplates);
}

void Templates::createFolders()
{
    if (!QDir().exists(pathFolderTemplates) && !QDir().mkpath(pathFolderTemplates)) {
        qDebug() << "Can not create folder: %1" << pathFolderTemplates << Qt::endl;
    }
}

OneTemplate Templates::createOneTemplateFromObj(const QJsonObject &objReplacer, const QString &name)
{
    OneTemplate oneTemplate;
    oneTemplate.name = name;
    const QJsonObject objEffects = objReplacer.value("effects").toObject();
    const auto keys = objReplacer.keys();
    for (const auto &key: keys) {
        Replacer replacer;
        replacer.word = key;
        replacer.tags = objReplacer.value(key).toString();
        oneTemplate.vecReplacers.append(replacer);
    }
    return oneTemplate;
}

QJsonObject Templates::createObjFromOneTemplate(const OneTemplate &oneTemplate)
{
    QJsonObject objReplacer;
    for (const Replacer &replacer: oneTemplate.vecReplacers) {
        objReplacer.insert(replacer.word, replacer.tags);
    }
    return objReplacer;
}
