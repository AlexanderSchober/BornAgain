// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      InputOutput/OutputDataWriteStrategy.h
//! @brief     Defines classes IOutputDataWriteStrategy and OutputDataWriteStreamIMA.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef OUTPUTDATAWRITESTRATEGY_H
#define OUTPUTDATAWRITESTRATEGY_H

#include "WinDllMacros.h"
#include <string>

template <class T> class OutputData;


//! @class IOutputDataWriteStrategy
//! @ingroup input_output
//! @brief Strategy interface to write OututData in file

class BA_CORE_API_ IOutputDataWriteStrategy
{
public:
    IOutputDataWriteStrategy() : m_precision(12) {}
    virtual ~IOutputDataWriteStrategy(){}

    virtual void writeOutputData(const OutputData<double>& data, std::ostream& output_stream) = 0;
protected:
    int m_precision;
};

//! @class OutputDataWriteINTStrategy
//! @ingroup input_output
//! @brief Strategy to write OutputData to special BornAgain ASCII format
class OutputDataWriteINTStrategy : public IOutputDataWriteStrategy
{
public:
    virtual void writeOutputData(const OutputData<double> &data, std::ostream &output_stream);
};

class TiffHandler;

//! @class OutputDataWriteTiffStrategy
//! @ingroup input_output
//! @brief Strategy to write OutputData to tiff files
class OutputDataWriteTiffStrategy : public IOutputDataWriteStrategy
{
public:
    OutputDataWriteTiffStrategy();
    ~OutputDataWriteTiffStrategy();
    virtual void writeOutputData(const OutputData<double> &data, std::ostream &output_stream);
private:
    TiffHandler *m_d;
};


#endif // OUTPUTDATAWRITESTRATEGY_H


