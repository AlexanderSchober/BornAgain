// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/InstrumentWidgets/BeamEditorWidget.h
//! @brief     Defines class BeamEditorWidget
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#ifndef BEAMEDITORWIDGET_H
#define BEAMEDITORWIDGET_H

#include "SessionItem.h"
#include "WinDllMacros.h"
#include <QWidget>

class BeamItem;
class ComponentEditor;
class QGridLayout;

class BA_CORE_API_ BeamEditorWidget : public QWidget
{
    Q_OBJECT
public:
    BeamEditorWidget(QWidget* parent = 0);

    void setBeamItem(BeamItem* beamItem);

    QGridLayout* gridLayout() { return m_gridLayout; }

private:
    void onDialogRequest(SessionItem* item, const QString& name);
    ComponentEditor* m_intensityEditor;
    ComponentEditor* m_wavelengthPresenter;
    ComponentEditor* m_inclinationAnglePresenter;
    ComponentEditor* m_azimuthalAnglePresenter;
    ComponentEditor* m_polarizationPresenter;
    QGridLayout* m_gridLayout;
    BeamItem* m_beamItem;
};

#endif // BEAMEDITORWIDGET_H
