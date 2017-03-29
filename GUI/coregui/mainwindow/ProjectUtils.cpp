// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/mainwindow/ProjectUtils.cpp
//! @brief     Implements ProjectUtils namespace
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2017
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   J. Burle, J. M. Fisher, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "ProjectUtils.h"
#include "projectdocument.h"
#include <QFileInfo>

QString ProjectUtils::projectName(const QString& projectFileName)
{
    QFileInfo info(projectFileName);
    return info.baseName();
}

QString ProjectUtils::projectDir(const QString& projectFileName)
{
    QFileInfo info(projectFileName);
    return info.path();
}

QString ProjectUtils::autosaveSubdir()
{
    return QStringLiteral("autosave");
}

//! From '/projects/Untitled2/Untitled2.pro' returns '/projects/Untitled2/autosave'.

QString ProjectUtils::autosaveDir(const QString& projectFileName)
{
    return ProjectUtils::projectDir(projectFileName) + "/" + autosaveSubdir();
}

//! From '/projects/Untitled2/Untitled2.pro' returns '/projects/Untitled2/autosave/Untitled2.pro'.

QString ProjectUtils::autosaveName(const QString& projectFileName)
{
    return ProjectUtils::autosaveDir(projectFileName) + "/" +
           ProjectUtils::projectName(projectFileName) + ProjectDocument::projectFileExtension();
}

bool ProjectUtils::hasAutosavedData(const QString& projectFileName)
{
    QFileInfo info(autosaveName(projectFileName));
    return info.exists();
}

