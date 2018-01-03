// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Computation/HashKVector.h
//! @brief     Defines class HashKVector.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef HASHKVECTOR_H
#define HASHKVECTOR_H

#include "Vectors3D.h"
#include <functional>
#include <utility>

class HashKVector
{
public:
    HashKVector() {}
    ~HashKVector() {}

    size_t operator()(kvector_t kvec) const noexcept;
private:
    std::hash<double> m_double_hash;
};

#endif // HASHKVECTOR_H
