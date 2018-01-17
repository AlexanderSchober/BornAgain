// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Beam/FootprintFactorSquare.h
//! @brief     Defines class FootprintFactorSquare.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef FOOTPRINTFACTORSQUARE_H_
#define FOOTPRINTFACTORSQUARE_H_

#include "IFootprintFactor.h"

//! Calculates footprint coefficient for a square beam
//! @ingroup simulation

class BA_CORE_API_ FootprintFactorSquare : public IFootprintFactor
{
public:
    using IFootprintFactor::IFootprintFactor;

    FootprintFactorSquare* clone() const override;

    //! Calculate footprint correction coefficient from the beam incident angle _alpha_.
    double calculate(double alpha) const override;

protected:
    FootprintFactorSquare(const FootprintFactorSquare& other);
};

#endif /* FOOTPRINTFACTORSQUARE_H_ */
