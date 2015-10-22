// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tools/inc/TiffReadStrategy.h
//! @brief     Defines class TiffReadStrategy.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef TIFFREADSTRATEGY_H
#define TIFFREADSTRATEGY_H

#include "WinDllMacros.h"
#include <string>
#include <boost/scoped_ptr.hpp>

template <class T> class OutputData;
class TiffHandler;

//! @class TiffReadStrategy
//! @ingroup tools
//! @brief Reads tiff files

class BA_CORE_API_ TiffReadStrategy
{
public:
    TiffReadStrategy();
    ~TiffReadStrategy();

    void read(const std::string &file_name);
//    void read(std::istream& input_stream);

private:
    TiffHandler *m_d;
};

#endif
