// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      InputOutput/OutputDataIOFactory.cpp
//! @brief     Implements class OutputDataIOFactory.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "IntensityDataIOFactory.h"
#include "OutputDataReadFactory.h"
#include "OutputDataWriteFactory.h"
#include "Exceptions.h"
#include "Utils.h"
#include "IHistogram.h"
#include <boost/scoped_ptr.hpp>

/* ************************************************************************* */
// reading output data
/* ************************************************************************* */
OutputData<double > *IntensityDataIOFactory::readOutputData(
        const std::string& file_name)
{
    boost::scoped_ptr<OutputDataReader> P_reader(OutputDataReadFactory::getReader(file_name));
    return P_reader->getOutputData();
}

IHistogram *IntensityDataIOFactory::readHistogram(const std::string &file_name)
{
    boost::scoped_ptr<OutputData<double> > data(readOutputData(file_name));
    return IHistogram::createHistogram(*data);
}

IHistogram *IntensityDataIOFactory::readIntensityData(const std::string &file_name)
{
    return readHistogram(file_name);
}



/* ************************************************************************* */
// writing output data
/* ************************************************************************* */
void IntensityDataIOFactory::writeOutputData(const OutputData<double>& data,
        const std::string& file_name)
{
    boost::scoped_ptr<OutputDataWriter> P_writer(OutputDataWriteFactory::getWriter(file_name));
    return P_writer->writeOutputData(data);
}

//void IntensityDataIOFactory::writeOutputData(const IHistogram &histogram,
//                                                const std::string &file_name)
//{
//    writeHistogram(histogram, file_name);
//}

void IntensityDataIOFactory::writeHistogram(const IHistogram &histogram,
                                                const std::string &file_name)
{
    boost::scoped_ptr<OutputData<double> > data(histogram.createOutputData());
    writeOutputData(*data, file_name);
}

void IntensityDataIOFactory::writeIntensityData(const IHistogram &histogram, const std::string &file_name)
{
    writeHistogram(histogram, file_name);
}

