// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Basics/ICloneable.h
//! @brief     Defines the standard mix-in ICloneable.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef ICLONEABLE_H
#define ICLONEABLE_H

#include "INoncopyable.h"
#include "WinDllMacros.h"

//! Mix-in for objects that must not be copied, except by cloning.
//! @ingroup tools_internal
//!
//! The base class INoncopyable disables the copy constructor and the operator=
//! in all its child classes.
//! Child classes of ICloneable should provide clone().

class BA_CORE_API_ ICloneable : public INoncopyable
{
public:
    virtual ICloneable* clone() const = 0;
    virtual void transferToCPP() {} //!< Used for Python overriding of clone
};

#endif // ICLONEABLE_H