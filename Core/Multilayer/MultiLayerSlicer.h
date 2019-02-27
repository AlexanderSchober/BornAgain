// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Multilayer/MultiLayerSlicer.h
//! @brief     Defines class MultiLayerSlicer.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef MULTILAYERSLICER_H
#define MULTILAYERSLICER_H

#include "WinDllMacros.h"
#include <memory>
#include <string>

class MultiLayer;

class BA_CORE_API_ MultiLayerSlicer
{
public:
    MultiLayerSlicer(const MultiLayer& multilayer);
    ~MultiLayerSlicer();

    std::string slicedRepresentation() const;
private:
    std::unique_ptr<MultiLayer> mP_multilayer;
};


#endif // MULTILAYERSLICER_H
