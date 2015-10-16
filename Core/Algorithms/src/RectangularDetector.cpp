// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Algorithms/src/RectangularDetector.cpp
//! @brief     Implements class RectangularDetector.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "RectangularDetector.h"
#include "MessageService.h"
#include "BornAgainNamespace.h"
#include "FixedBinAxis.h"
#include "ConstKBinAxis.h"
#include "CustomBinAxis.h"
#include "Beam.h"
#include "Rectangle.h"

#include <iostream>

RectangularDetector::RectangularDetector(kvector_t normal_to_detector, kvector_t u_direction)
    : m_normal_to_detector(normal_to_detector)
{
    double d2 = m_normal_to_detector.dot(m_normal_to_detector);
    m_u_unit = normalizeToUnitLength(
        d2 * u_direction - u_direction.dot(m_normal_to_detector) * m_normal_to_detector);
    m_v_unit = normalizeToUnitLength(m_u_unit.cross(m_normal_to_detector));
    setName("RectangularDetector");
    init_parameters();
}

RectangularDetector::RectangularDetector(const RectangularDetector &other)
    : IDetector2D(other)
    , m_normal_to_detector(other.m_normal_to_detector)
    , m_u_unit(other.m_u_unit), m_v_unit(other.m_v_unit)
{
    setName("RectangularDetector");
    init_parameters();
}

RectangularDetector &RectangularDetector::operator=(const RectangularDetector &other)
{
    if (this != &other) {
        RectangularDetector tmp(other);
        tmp.swapContent(*this);
    }
    return *this;
}

RectangularDetector *RectangularDetector::clone() const
{
    return new RectangularDetector(*this);
}

IPixelMap *RectangularDetector::createPixelMap(size_t index) const
{
    const IAxis &u_axis = getAxis(BornAgain::X_AXIS_INDEX);
    const IAxis &v_axis = getAxis(BornAgain::Y_AXIS_INDEX);
    size_t u_index = getAxisBinIndex(index, BornAgain::X_AXIS_INDEX);
    size_t v_index = getAxisBinIndex(index, BornAgain::Y_AXIS_INDEX);

    Bin1D u_bin = u_axis.getBin(u_index);
    Bin1D v_bin = v_axis.getBin(v_index);
    kvector_t corner_position = m_normal_to_detector
            + u_bin.m_lower*m_u_unit + v_bin.m_lower*m_v_unit;
    kvector_t width = u_bin.getBinSize()*m_u_unit;
    kvector_t height = v_bin.getBinSize()*m_v_unit;
    return new RectPixelMap(corner_position, width, height);
}

std::string RectangularDetector::addParametersToExternalPool(std::string path, ParameterPool *external_pool,
                                                  int copy_number) const
{
    // add own parameters
    std::string new_path
        = IParameterized::addParametersToExternalPool(path, external_pool, copy_number);

    // add parameters of the resolution function
    if (mP_detector_resolution) {
        mP_detector_resolution->addParametersToExternalPool(new_path, external_pool, -1);
    }
    return new_path;
}

void RectangularDetector::print(std::ostream &ostr) const
{
    ostr << "RectangularDetector: '" << getName() << "' " << m_parameters;
    for (size_t i = 0; i < m_axes.size(); ++i) {
        ostr << "    IAxis:" << *m_axes[i] << std::endl;
    }
}

std::string RectangularDetector::getAxisName(size_t index) const
{
    switch (index) {
    case 0:
        return BornAgain::U_AXIS_NAME;
        break;
    case 1:
        return BornAgain::V_AXIS_NAME;
        break;
    default:
        throw LogicErrorException(
            "SphericalDetector::getAxisName(size_t index) -> Error! index > 1");
    }
}

void RectangularDetector::swapContent(RectangularDetector &other)
{
    IDetector2D::swapContent(other);
    std::swap(this->m_normal_to_detector, other.m_normal_to_detector);
    std::swap(this->m_u_unit, other.m_u_unit);
    std::swap(this->m_v_unit, other.m_v_unit);
}

kvector_t RectangularDetector::normalizeToUnitLength(const kvector_t &direction) const
{
    double old_length = direction.mag();
    if (old_length==0.0) return direction;
    return direction/old_length;
}

RectPixelMap::RectPixelMap(kvector_t corner_pos, kvector_t width, kvector_t height)
    : m_corner_pos(corner_pos), m_width(width), m_height(height)
{
    m_normal = m_width.cross(m_height);
    m_solid_angle = calculateSolidAngle();
}

RectPixelMap *RectPixelMap::clone() const
{
    return new RectPixelMap(m_corner_pos, m_width, m_height);
}

RectPixelMap *RectPixelMap::createZeroSizeMap(double x, double y) const
{
    kvector_t position = m_corner_pos + x*m_width + y*m_height;
    kvector_t null_vector;
    return new RectPixelMap(position, null_vector, null_vector);
}

kvector_t RectPixelMap::getK(double x, double y, double wavelength) const
{
    kvector_t direction = m_corner_pos + x*m_width + y*m_height;
    double length = 2.0*M_PI/wavelength;
    return normalizeLength(direction, length);
}

double RectPixelMap::getIntegrationFactor(double x, double y) const
{
    if (m_solid_angle==0.0) return 1.0;
    kvector_t position = m_corner_pos + x*m_width + y*m_height;
    double length = position.mag();
    return std::abs(position.dot(m_normal))/std::pow(length, 3)/m_solid_angle;
}

double RectPixelMap::getSolidAngle() const
{
    if (m_solid_angle<=0.0) return 1.0;
    return m_solid_angle;
}

kvector_t RectPixelMap::normalizeLength(const kvector_t &direction, double length) const
{
    double old_length = direction.mag();
    if (old_length==0.0) return direction;
    return direction*length/old_length;
}

double RectPixelMap::calculateSolidAngle() const
{
    kvector_t position = m_corner_pos + 0.5*m_width + 0.5*m_height;
    double length = position.mag();
    return std::abs(position.dot(m_normal))/std::pow(length, 3);
}

