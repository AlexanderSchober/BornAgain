// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      StandardSamples/IsGISAXS01Builder.h
//! @brief     Defines class IsGISAXS01Builder.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef ISGISAXS01BUILDER_H
#define ISGISAXS01BUILDER_H

#include "ISampleBuilder.h"

//! @class IsGISAXS01Builder
//! @ingroup standard_samples
//! @brief Builds sample: mixture of cylinders and prisms without interference
//! (IsGISAXS example #1)

class BA_CORE_API_ IsGISAXS01Builder : public ISampleBuilder
{
public:
    IsGISAXS01Builder();
    ISample *buildSample() const;

protected:
    void init_parameters();

private:
    double m_cylinder_height;
    double m_cylinder_radius;
    double m_prism_height;
    double m_prism_length;
    double m_cylinder_weight;
};

#endif // ISGISAXS01BUILDER_H
