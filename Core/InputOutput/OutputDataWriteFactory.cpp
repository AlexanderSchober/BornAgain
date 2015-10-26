// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      InputOutput/OutputDataWriteFactory.cpp
//! @brief     Implements class OutputDataWriteFactory.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //
#include "OutputDataWriteFactory.h"
#include "OutputDataWriter.h"
#include "Exceptions.h"
#include "OutputDataWriteStrategy.h"
#include "OutputDataIOHelper.h"

OutputDataWriter *OutputDataWriteFactory::getWriter(const std::string &file_name)
{
    OutputDataWriter *result = new OutputDataWriter(file_name);
    result->setStrategy(getWriteStrategy(file_name));
    return result;
}


IOutputDataWriteStrategy *OutputDataWriteFactory::getWriteStrategy(const std::string &file_name)
{
    IOutputDataWriteStrategy *result(0);
    if(OutputDataIOHelper::isIntFile(file_name)) {
        result = new OutputDataWriteStreamINT();
    }

    else {
        throw LogicErrorException("OutputDataWriteFactory::getWriter() -> Error. "
                "Don't know how to write file '" + file_name+std::string("'"));
    }

    return result;
}
