// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tools/inc/FixedBinAxis.h
//! @brief     Defines class FixedBinAxis.
//!
//! @homepage  http://apps.jcns.fz-juelich.de/BornAgain
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef FIXEDBINAXIS_H
#define FIXEDBINAXIS_H


#include "IAxis.h"

//! @class FixedBinAxis
//! @ingroup tools
//! @brief Axis with fixed bin size.

class BA_CORE_API_ FixedBinAxis : public IAxis
{
public:
    FixedBinAxis(std::string name);

    //! @brief FixedBinAxis constructor
    //! @param name Axis name
    //! @param nbins number of bins
    //! @param start low edge of first bin
    //! @param end upper edge of last bin
    FixedBinAxis(std::string name, size_t nbins, double start, double end);
    virtual ~FixedBinAxis() {}

    FixedBinAxis *clone() const;

    size_t getSize() const;

    double operator[](size_t index) const;

    Bin1D getBin(size_t index) const;

    double getMin() const;

    double getMax() const;

    size_t findClosestIndex(double value) const;

    std::vector<double > getBinCenters() const;

    std::vector<double > getBinBoundaries() const;

protected:
    void print(std::ostream& ostr) const;
    virtual bool equals(const IAxis& other) const;

private:
    size_t m_nbins;
    double m_start;
    double m_end;
};



#endif
