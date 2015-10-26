// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      InputOutput/OutputDataWriteFactory.h
//! @brief     Defines class OutputDataWriteFactory.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef OUTPUTDATAWRITEFACTORY_H
#define OUTPUTDATAWRITEFACTORY_H

#include <string>
#include "WinDllMacros.h"
#include "OutputDataWriter.h"

class IOutputDataWriteStrategy;

//! @class OutputDataWriteFactory
//! @ingroup input_output
//! @brief Creates writer appropariate for given type of files

class BA_CORE_API_ OutputDataWriteFactory
{
public:
    static OutputDataWriter* getWriter(const std::string& file_name);

private:
    static IOutputDataWriteStrategy *getWriteStrategy(const std::string& file_name);
};

#endif
