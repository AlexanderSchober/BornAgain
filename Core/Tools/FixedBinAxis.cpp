// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tools/FixedBinAxis.cpp
//! @brief     Implement class FixedBinAxis.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "FixedBinAxis.h"
#include "Exceptions.h"
#include <iomanip>


FixedBinAxis::FixedBinAxis(const std::string &name, size_t nbins, double start, double end)
    : IAxis(name), m_nbins(nbins), m_start(start), m_end(end)
{
}

FixedBinAxis *FixedBinAxis::clone() const
{
    FixedBinAxis *result = new FixedBinAxis(getName(), m_nbins, m_start, m_end);
    return result;
}

size_t FixedBinAxis::getSize() const
{
    return m_nbins;
}

double FixedBinAxis::operator[](size_t index) const
{
    if(index >= m_nbins)
        throw Exceptions::OutOfBoundsException("FixedBinAxis::operator[] -> Error. Wrong index.");

    double step = (m_end - m_start)/m_nbins;
    return m_start + (index + 0.5)*step;
}

Bin1D FixedBinAxis::getBin(size_t index) const
{
    if(index >= m_nbins)
        throw Exceptions::OutOfBoundsException("FixedBinAxis::getBin() -> Error. Wrong index.");

    double step = (m_end - m_start)/m_nbins;
    Bin1D result( m_start + step*index, m_start + step*(index+1) );
    return result;
}

double FixedBinAxis::getMin() const
{
    return m_start;
}

double FixedBinAxis::getMax() const
{
    return m_end;
}

double FixedBinAxis::getBinCenter(size_t index) const
{
    return (*this)[index];
}

size_t FixedBinAxis::findClosestIndex(double value) const
{
    if( value < getMin()) {
        return 0;
    } else if(value >= getMax()) {
        return m_nbins-1;
    }

    double step = (m_end - m_start)/m_nbins;
    return int( (value-m_start)/step);
}

std::vector<double> FixedBinAxis::getBinCenters() const
{
    std::vector<double> result;
    result.resize(getSize(), 0.0);
    for(size_t i=0; i<getSize(); ++i) {
        result[i] = getBin(i).getMidPoint();
    }
    return result;
}

std::vector<double> FixedBinAxis::getBinBoundaries() const
{
    std::vector<double> result;
    result.resize(getSize()+1, 0.0);
    for(size_t i=0; i<getSize(); ++i) {
        result[i] = getBin(i).m_lower;
    }
    result[getSize()] = getBin(getSize()-1).m_upper;
    return result;
}

FixedBinAxis *FixedBinAxis::createClippedAxis(double left, double right) const
{
    if(left >= right)
        throw LogicErrorException("FixedBinAxis::createClippedAxis() -> Error. 'left'' should be smaller than 'right'");

    if(left < getMin()) left = getBin(0).getMidPoint();
    if(right >= getMax()) right = getBin(getSize()-1).getMidPoint();

    size_t nbin1 = findClosestIndex(left);
    size_t nbin2 = findClosestIndex(right);

    return new FixedBinAxis(getName(), nbin2-nbin1+1, getBin(nbin1).m_lower, getBin(nbin2).m_upper );
}

void FixedBinAxis::print(std::ostream& ostr) const
{
    ostr << "FixedBinAxis(\"" << m_name << "\", " << getSize() << ", "
         << std::setprecision(std::numeric_limits<double>::digits10+2) << getMin() << ", "
         << getMax() << ")";
}

bool FixedBinAxis::equals(const IAxis& other) const
{
    if (!IAxis::equals(other)) return false;
    if (const FixedBinAxis *otherAxis = dynamic_cast<const FixedBinAxis *>(&other)) {
        if (getSize() != otherAxis->getSize()) return false;
        if ( !Numeric::areAlmostEqual(m_start, otherAxis->m_start)) return false;
        if ( !Numeric::areAlmostEqual(m_end, otherAxis->m_end)) return false;
        return true;
    }
    return false;
}
