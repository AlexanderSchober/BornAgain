// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/InstrumentWidgets/SphericalDetectorWidget.h
//! @brief     Defines class SphericalDetectorWidget
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#ifndef SPHERICALDETECTORWIDGET_H
#define SPHERICALDETECTORWIDGET_H

#include "WinDllMacros.h"
#include <QWidget>

class QGridLayout;
class ColumnResizer;
class ComponentEditor;
class SessionItem;

//! Widget for editing a spherical detector settings

class BA_CORE_API_ SphericalDetectorWidget : public QWidget
{
    Q_OBJECT
public:
    SphericalDetectorWidget(ColumnResizer* columnResizer, SessionItem* detectorItem,
                            QWidget* parent = 0);
    virtual ~SphericalDetectorWidget();

    void setDetectorItem(SessionItem* detectorItem);

public slots:
    void onColumnResizerDestroyed(QObject* object);

private:
    ColumnResizer* m_columnResizer;
    ComponentEditor* m_phiAxisEditor;
    ComponentEditor* m_alphaAxisEditor;
    ComponentEditor* m_resolutionFunctionEditor;
    ComponentEditor* m_polarizationAnalysisEditor;
    QGridLayout* m_gridLayout;
};

#endif // SPHERICALDETECTORWIDGET_H
