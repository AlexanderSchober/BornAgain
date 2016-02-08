// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Views/FitView.h
//! @brief     Defines class FitView
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef FITVIEW_H
#define FITVIEW_H

#include <WinDllMacros.h>
#include <QWidget>

class MainWindow;
class RunFitWidget;
class QLineEdit;
class ColorMapPlot;

class BA_CORE_API_ FitView : public QWidget
{
    Q_OBJECT
public:
    FitView(MainWindow *window);

public slots:
    void onUpdatePath();

private:
    RunFitWidget *m_runFitWidget;
    QLineEdit *m_line;
    ColorMapPlot *m_testplot;
};

#endif
