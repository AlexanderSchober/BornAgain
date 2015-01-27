// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Models/MaterialItem.h
//! @brief     Defines class MaterialItem
//!
//! @homepage  http://bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef MATERIALITEM_H
#define MATERIALITEM_H


#include "ParameterizedItem.h"
#include <QColor>

class BA_CORE_API_ MaterialItem : public ParameterizedItem
{
    Q_OBJECT
public:

    static const QString P_MATERIAL_TYPE;
    static const QString P_COLOR;
    static const QString P_REFRACTIVE_INDEX;
    static const QString P_MAGNETIC_FIELD;
    static const QString P_IDENTIFIER;
    explicit MaterialItem(ParameterizedItem *parent=0);
    ~MaterialItem(){}
    void setMaterialType(int index);

    QString getIdentifier() const;

    QColor getColor() const;

    bool isHomogeneousMaterial() const;

    bool isHomogeneousMagneticMaterial() const;
};

#endif
