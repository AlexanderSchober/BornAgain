// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Geometry/src/Polygon.cpp
//! @brief     Implements class Polygon.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "Polygon.h"
#include "Bin.h"
#include <boost/geometry.hpp>
#include <boost/geometry/geometries/point_xy.hpp>
#include <boost/geometry/geometries/polygon.hpp>
#include <iostream>

using namespace boost::geometry;

namespace Geometry {

//! The private data for polygons to hide boost dependency from the header
class PolygonPrivate {
public:
    typedef model::d2::point_xy<double> point_t;
    typedef model::polygon<point_t> polygon_t;
    polygon_t polygon;
    void init_from(const std::vector<double> &x, const std::vector<double> &y);
};


void PolygonPrivate::init_from(const std::vector<double> &x, const std::vector<double> &y)
{
    if(x.size() != y.size()) {
        std::ostringstream message;
        message << "Polygon::Polygon(const std::vector<double> &x, const std::vector<double> &y) "
                << "Error. Sizes of arrays must conincide." << std::endl;
        throw LogicErrorException(message.str());
    }
    std::vector<point_t> points;
    for(size_t i=0; i<x.size(); ++i) {
        points.push_back(point_t(x[i], y[i]));
    }
    assign_points(polygon, points);
    correct(polygon);
}


// IMPORTANT Input parameters are not "const reference" to be able to work from python
// (auto convertion of python list to vector<double>).
Polygon::Polygon(std::vector<double> x, std::vector<double> y)
    : m_d(new PolygonPrivate)
{
    m_d->init_from(x, y);
}

// IMPORTANT Input parameter is not "const reference" to be able to work from python
// (auto convertion of python list to vector<vector<double>>).
Polygon::Polygon(std::vector<std::vector<double> > points)
    : m_d(new PolygonPrivate)
{
    std::vector<double> x;
    std::vector<double> y;
    for(size_t i=0; i<points.size(); ++i) {
        if(points[i].size() != 2) {
            std::ostringstream message;
            message << "Polygon(const std::vector<std::vector<double> > &points) -> Error. "
                    << " Should be two-dimensional array with second dimension of 2 size."
                    << std::endl;
            throw LogicErrorException(message.str());
        }
        x.push_back(points[i][0]);
        y.push_back(points[i][1]);
    }

    m_d->init_from(x, y);
}

Polygon::~Polygon()
{
    delete m_d;
}

Polygon *Polygon::clone() const
{
    return new Polygon(*this);
}

bool Polygon::contains(double x, double y) const
{
//    return within(PolygonPrivate::point_t(x, y), m_d->polygon); // not including borders
    return covered_by(PolygonPrivate::point_t(x, y), m_d->polygon); // including borders
}

bool Polygon::contains(const Bin1D &binx, const Bin1D &biny) const
{
    return contains(binx.getMidPoint(), biny.getMidPoint());
}

double Polygon::getArea() const
{
    return area(m_d->polygon);
}

void Polygon::print(std::ostream &ostr) const
{
    ostr << wkt<PolygonPrivate::polygon_t>(m_d->polygon);
}

Polygon::Polygon(const Polygon &other)
{
    m_d = new PolygonPrivate(*other.m_d);
}

} // namespace Geometry
