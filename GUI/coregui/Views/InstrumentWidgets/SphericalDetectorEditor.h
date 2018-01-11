// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/InstrumentWidgets/SphericalDetectorEditor.h
//! @brief     Defines class SphericalDetectorEditor
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef SPHERICALDETECTOREDITOR_H
#define SPHERICALDETECTOREDITOR_H

#include "SessionItemWidget.h"
class SphericalDetectorItem;

class BA_CORE_API_ SphericalDetectorEditor : public SessionItemWidget
{
    Q_OBJECT
public:
    SphericalDetectorEditor(QWidget* parent = nullptr);

protected:
    SphericalDetectorItem* detectorItem();

    void subscribeToItem();
    void unsubscribeFromItem();

};

#endif  // SPHERICALDETECTOREDITOR_H
