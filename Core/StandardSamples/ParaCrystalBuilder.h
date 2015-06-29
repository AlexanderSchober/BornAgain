// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      StandardSamples/ParaCrystalBuilder.h
//! @brief     Defines classes of ParaCrystalBuilder family.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef PARACRYSTALBUILDER_H
#define PARACRYSTALBUILDER_H

#include "ISampleBuilder.h"

//! @class RadialParaCrystalBuilder
//! @ingroup standard_samples
//! @brief Builds sample: cylinders with 1DDL structure factor (IsGISAXS example #4)

class BA_CORE_API_ RadialParaCrystalBuilder : public ISampleBuilder
{
public:
    RadialParaCrystalBuilder();
    ISample *buildSample() const;

protected:
    void init_parameters();

private:
    double m_corr_peak_distance;
    double m_corr_width;
    double m_corr_length;
    double m_cylinder_height;
    double m_cylinder_radius;
};

//! @class HexParaCrystalBuilder
//! @ingroup standard_samples
//! @brief Builds sample: cylinders with 2DDL structure factor (IsGISAXS example #4)

class BA_CORE_API_ HexParaCrystalBuilder : public ISampleBuilder
{
public:
    HexParaCrystalBuilder();
    ISample *buildSample() const;

protected:
    void init_parameters();

private:
    double m_peak_distance;
    double m_corr_length;
    double m_domain_size_1;
    double m_domain_size_2;
    double m_cylinder_height;
    double m_cylinder_radius;
};

//! @class RectParaCrystalBuilder
//! @ingroup standard_samples
//! @brief Builds sample:  2D paracrystal lattice (IsGISAXS example #8)

class BA_CORE_API_ RectParaCrystalBuilder : public ISampleBuilder
{
public:
    RectParaCrystalBuilder();
    ISample *buildSample() const;
};


//! @class IsGISAXS08BBuilder TODO remove it completely
//! @ingroup standard_samples
//! @brief Builds sample:  2D paracrystal lattice with isotropic pdfs (IsGISAXS example #8)

class BA_CORE_API_ IsGISAXS08BBuilder : public ISampleBuilder
{
public:
    IsGISAXS08BBuilder();
    ISample *buildSample() const;
};




#endif // PARACRYSTALBUILDER_H
