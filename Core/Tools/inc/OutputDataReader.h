// ************************************************************************** //
//                                                                           
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @copyright Forschungszentrum Jülich GmbH 2013
//             
//  Homepage:  apps.jcns.fz-juelich.de/BornAgain
//  License:   GNU General Public License v3 or higher (see COPYING)
//
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke 
//
//! @file      Tools/OutputDataReader.h 
//! @brief     Defines class OutputDataReader.
//
// ************************************************************************** //

#ifndef OUTPUTDATAREADER_H
#define OUTPUTDATAREADER_H

#include "OutputData.h"
#include "OutputDataReadStrategy.h"
#include "Types.h"
#include <string>

//! Reads OutputData from file using different reading strategies.

class OutputDataReader
{
public:
    OutputDataReader() : m_read_strategy(0) {}
    OutputDataReader(const std::string &file_name) : m_file_name(file_name), m_read_strategy(0) {}
    OutputDataReader(IOutputDataReadStrategy *read_strategy) : m_read_strategy(read_strategy) {}
    virtual ~OutputDataReader() { delete m_read_strategy; }

    //! read output data from file (file name was set already from OutputDataIOFactory)
//    OutputData<double > *getOutputData() { return getOutputData(m_file_name); }
    OutputData<double > *getOutputData();

    //! set concrete reading strategy
    void setStrategy(IOutputDataReadStrategy *read_strategy) { delete m_read_strategy; m_read_strategy = read_strategy; }

private:
//    //! read output data from file
//    OutputData<double > *getOutputData(const std::string &file_name);

    std::string m_file_name;
    IOutputDataReadStrategy *m_read_strategy;
};

#endif // OUTPUTDATAREADER_H
