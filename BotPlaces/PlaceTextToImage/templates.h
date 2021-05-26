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

#pragma once

#include <QObject>
#include <QDir>
#include <QFileInfo>
#include <QDebug>

#include "FileWorker.h"
#include "OneTemplate.h"


class Templates
{
public:
    Templates();

    static void initValues();
    static void loadAllTemplates();
    static OneTemplate getTemplate(const QString &nameTemplate);
    static void addNewTemplate(const OneTemplate &oneTemplate);

private:
    static void createFolders();
    static OneTemplate createOneTemplateFromObj(const QJsonObject &objReplacer, const QString &name);
    static QJsonObject createObjFromOneTemplate(const OneTemplate &oneTemplate);

private:
    static QString pathFolderTemplates;
    static QString fileTemplates;
    static QScopedPointer<QVector<OneTemplate> > vecTemplates;
};

