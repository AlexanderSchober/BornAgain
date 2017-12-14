// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/mainwindow/OutputDataIOService.h
//! @brief     Implements class OutputDataIOService
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2017
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   J. Burle, J. M. Fisher, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "OutputDataIOService.h"
#include "ApplicationModels.h"
#include "IntensityDataItem.h"
#include "JobItemUtils.h"
#include "ProjectUtils.h"
#include "MessageService.h"

OutputDataIOService::OutputDataIOService(QObject* parent)
    : QObject(parent), m_applicationModels(nullptr)
{
    setObjectName("OutputDataIOService");
}

OutputDataIOService::OutputDataIOService(ApplicationModels* models, QObject* parent)
    : QObject(parent), m_applicationModels(nullptr)
{
    setObjectName("OutputDataIOService");
    setApplicationModels(models);
}

void OutputDataIOService::setApplicationModels(ApplicationModels* models)
{
    m_applicationModels = models;
}

void OutputDataIOService::save(const QString& projectDir)
{
    if (!m_history.hasHistory(projectDir))
        m_history.setHistory(projectDir, OutputDataDirHistory());

    OutputDataDirHistory newHistory;

    for (auto item : dataItems()) {

        if (m_history.wasModifiedSinceLastSave(projectDir, item))
            JobItemUtils::saveIntensityData(item, projectDir);

        newHistory.markAsSaved(item);
    }

    // dealing with files
    QStringList oldFiles = m_history.savedFileNames(projectDir);
    QStringList newFiles = newHistory.savedFileNames();
    cleanOldFiles(projectDir, oldFiles, newFiles);

    // if oldHistory contained some deleted IntensityDataItems, that info will be dropped here
    m_history.setHistory(projectDir, newHistory);
}

void OutputDataIOService::load(const QString& projectDir, MessageService* messageService)
{
    OutputDataDirHistory newHistory;

    for (auto item : dataItems()) {

        try {
            JobItemUtils::loadIntensityData(item, projectDir);
            newHistory.markAsSaved(item);
        } catch (const std::exception& ex) {
            if (messageService)
                messageService->send_message(this, "FIXME", QString(ex.what()));
            else
                throw ex;
        }

    }

    m_history.setHistory(projectDir, newHistory);
}

//! Returns all IntensityDataItems available for save/load.

QVector<IntensityDataItem*> OutputDataIOService::dataItems() const
{
    QVector<IntensityDataItem*> result;

    if (!m_applicationModels)
        return result;

    for (auto item : m_applicationModels->nonXMLData()) {
        if (auto intensityItem = dynamic_cast<IntensityDataItem*>(item))
            result.push_back(intensityItem);
    }

    return result;
}

//! Clean old saved files.
//! All files in oldSaves list, which are not in newSaves list, will be removed.

void OutputDataIOService::cleanOldFiles(const QString& projectDir, const QStringList& oldSaves,
                                        const QStringList& newSaves)
{
    QStringList to_remove = ProjectUtils::substract(oldSaves, newSaves);
    ProjectUtils::removeFiles(projectDir, to_remove);
}
