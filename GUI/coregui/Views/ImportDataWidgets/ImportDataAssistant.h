// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/ImportDataWidgets/ImportDataAssistant.h
//! @brief     Defines class ImportDataAssistant
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#ifndef IMPORTDATAASSISTANT_H
#define IMPORTDATAASSISTANT_H

#include "WinDllMacros.h"

template <class T> class OutputData;
class RealDataItem;
class QString;

//! The ImportDataAssistant class provides utility methods to import data files.

class BA_CORE_API_ ImportDataAssistant {
public:

    OutputData<double> *importData(QString &baseNameOfLoadedFile);

    static void loadIntensityData(RealDataItem *realDataItem, const QString &projectDir);
    static void saveIntensityData(RealDataItem *realDataItem, const QString &projectDir);

    OutputData<double> *createSimlifiedOutputData(const OutputData<double> &data);

};

#endif // IMPORTDATAASSISTANT_H
