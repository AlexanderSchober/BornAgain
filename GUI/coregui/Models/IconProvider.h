// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Models/IconProvider.h
//! @brief     Defines class IconProvider
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef ICON_PROVIDER_H
#define ICON_PROVIDER_H

#include "WinDllMacros.h"
#include <QIcon>
#include <QString>

//! Class which returns icons for ParameterizedItems to use in SessionModel
class BA_CORE_API_ IconProvider
{
public:
    IconProvider(){}
    virtual ~IconProvider(){}

    virtual QIcon icon(const QString &modelType);

};


#endif

