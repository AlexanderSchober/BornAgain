// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      StandardSamples/IsGISAXS09Builder.h
//! @brief     Defines classes IsGISAXS09ABuilder and IsGISAXS09BBuilder.
//!
//! @homepage  http://bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef ISGISAXS09BUILDER_H
#define ISGISAXS09BUILDER_H

#include "ISampleBuilder.h"

//! @class IsGISAXS09ABuilder
//! @ingroup standard_samples
//! @brief Builds sample:  Pyramids, pyramids on top of substrate
//!(IsGISAXS example #9)

class BA_CORE_API_ IsGISAXS09ABuilder : public ISampleBuilder
{
public:
    IsGISAXS09ABuilder();
    ISample *buildSample() const;

protected:
    void init_parameters();

private:
    double m_length;
    double m_height;
    double m_alpha;
};

//! @class IsGISAXS09BBuilder
//! @ingroup standard_samples
//! @brief Builds sample:  Pyramids, rotated pyramids on top of substrate
//!(IsGISAXS example #9)

class BA_CORE_API_ IsGISAXS09BBuilder : public ISampleBuilder
{
public:
    IsGISAXS09BBuilder();
    ISample *buildSample() const;

protected:
    void init_parameters();

private:
    double m_length;
    double m_height;
    double m_alpha;
    double m_zangle;
};


#endif // ISGISAXS09BUILDER_H
