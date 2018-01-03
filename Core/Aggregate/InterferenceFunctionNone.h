// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Aggregate/InterferenceFunctionNone.h
//! @brief     Defines class InterferenceFunctionNone.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef INTERFERENCEFUNCTIONNONE_H
#define INTERFERENCEFUNCTIONNONE_H

#include "IInterferenceFunction.h"

//! Default interference function (i.e. absence of any interference).
//! @ingroup interference

class BA_CORE_API_ InterferenceFunctionNone : public IInterferenceFunction
{
public:
    InterferenceFunctionNone();

    InterferenceFunctionNone* clone() const final { return new InterferenceFunctionNone(); }

    void accept(INodeVisitor* visitor) const final { visitor->visit(this); }

    double evaluate(const kvector_t) const final { return 1; }
};

#endif // INTERFERENCEFUNCTIONNONE_H
