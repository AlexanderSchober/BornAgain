// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Models/LatticeTypeItems.h
//! @brief     Defines classes LatticeTypeItems
//!
//! @homepage  http://bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef LATTICETYPEITEMS_H
#define LATTICETYPEITEMS_H

#include "ParameterizedItem.h"

class BA_CORE_API_ BasicLatticeTypeItem : public ParameterizedItem
{
    Q_OBJECT
public:
    static const QString P_LATTICE_LENGTH1;
    static const QString P_LATTICE_LENGTH2;
    static const QString P_LATTICE_ANGLE;
    explicit BasicLatticeTypeItem(ParameterizedItem *parent=0);
    ~BasicLatticeTypeItem(){}
};

class BA_CORE_API_ SquareLatticeTypeItem : public ParameterizedItem
{
    Q_OBJECT
public:
    static const QString P_LATTICE_LENGTH;
    explicit SquareLatticeTypeItem(ParameterizedItem *parent=0);
    ~SquareLatticeTypeItem(){}
};

class BA_CORE_API_ HexagonalLatticeTypeItem : public ParameterizedItem
{
    Q_OBJECT
public:
    static const QString P_LATTICE_LENGTH;
    explicit HexagonalLatticeTypeItem(ParameterizedItem *parent=0);
    ~HexagonalLatticeTypeItem(){}
};

#endif
