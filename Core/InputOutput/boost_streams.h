// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/InputOutput/boost_streams.h
//! @brief     Contains boost streams related headers
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BOOST_STREAMS_H
#define BOOST_STREAMS_H

#include "Macros.h"
GCC_DIAG_OFF(unused-parameter)
#include <boost/iostreams/filtering_stream.hpp>
#include <boost/iostreams/copy.hpp>
#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable: 4244)
#endif
#include <boost/iostreams/filter/gzip.hpp>
#include <boost/iostreams/filter/bzip2.hpp>
#ifdef _MSC_VER
#pragma warning(pop)
#endif
GCC_DIAG_ON(unused-parameter)

#endif // BOOST_STREAMS_H

