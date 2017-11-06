// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/MaterialEditor/MaterialUtils.h
//! @brief     Defines class MaterialUtils
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#ifndef MATERIALUTILS_H
#define MATERIALUTILS_H

#include "ColorProperty.h"
#include "MaterialItem.h"
#include "MaterialProperty.h"
#include <QColor>
#include <QString>
#include <memory>

class Material;

namespace MaterialUtils
{

BA_CORE_API_ QColor suggestMaterialColor(const QString &name);
BA_CORE_API_ MaterialProperty getDefaultMaterialProperty();
BA_CORE_API_ ColorProperty suggestMaterialColorProperty(const QString &name);
BA_CORE_API_ std::unique_ptr<Material> createDomainMaterial(
        const MaterialProperty &material_property);

BA_CORE_API_ QString materialTag(const SessionItem &item);
}


#endif // MATERIALUTILS_H
