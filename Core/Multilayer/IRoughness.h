// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Multilayer/IRoughness.h
//! @brief     Defines and implements interface class IRoughness.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef IROUGHNESS_H
#define IROUGHNESS_H

#include "ISample.h"

//! Interface to equip an interface with a roughness.
//! @ingroup samples_internal

class BA_CORE_API_ IRoughness : public ISample
{
public:
    IRoughness() {}
    virtual ~IRoughness() {}
    virtual void accept(ISampleVisitor* visitor) const { visitor->visit(this); }
};

#endif // IROUGHNESS_H
