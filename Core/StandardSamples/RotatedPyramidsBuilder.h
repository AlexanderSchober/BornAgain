// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/StandardSamples/RotatedPyramidsBuilder.h
//! @brief     Declares class RotatedPyramidsBuilder.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef ROTATEDPYRAMIDSBUILDER_H
#define ROTATEDPYRAMIDSBUILDER_H


//! @class RotatedPyramidsBuilder
//! @ingroup standard_samples
//! @brief Builds sample:  Pyramids, rotated pyramids on top of substrate
//!(IsGISAXS example #9)

class BA_CORE_API_ RotatedPyramidsBuilder : public ISampleBuilder
{
public:
    RotatedPyramidsBuilder();
    ISample *buildSample() const;

protected:
    void init_parameters();

private:
    double m_length;
    double m_height;
    double m_alpha;
    double m_zangle;
};


#endif // ROTATEDPYRAMIDSBUILDER_H
