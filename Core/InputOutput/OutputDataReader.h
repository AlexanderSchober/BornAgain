// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      InputOutput/OutputDataReader.h
//! @brief     Defines class OutputDataReader.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef OUTPUTDATAREADER_H
#define OUTPUTDATAREADER_H

#include "WinDllMacros.h"
#include "OutputDataReadStrategy.h"
#include <string>
#include <vector>
#include <boost/scoped_ptr.hpp>

template <class T> class OutputData;

//! @class OutputDataReader
//! @ingroup input_output
//! @brief Reads OutputData from file using different reading strategies.

class BA_CORE_API_ OutputDataReader
{
public:
    OutputDataReader(const std::string& file_name);

    //! read output data from file (file name was set already from OutputDataIOFactory)
    OutputData<double > *getOutputData();

    //! Sets concrete reading strategy
    void setStrategy(IOutputDataReadStrategy *read_strategy);

private:
    std::vector<char> readBuffer(std::istream &input_stream);
    std::string m_file_name;
    boost::scoped_ptr<IOutputDataReadStrategy> m_read_strategy;
};

#endif // OUTPUTDATAREADER_H


