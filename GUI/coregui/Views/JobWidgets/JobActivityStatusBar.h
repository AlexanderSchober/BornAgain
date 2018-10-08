// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/JobWidgets/JobActivityStatusBar.h
//! @brief     Defines class JobActivityStatusBar
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef JOBACTIVITYSTATUSBAR_H
#define JOBACTIVITYSTATUSBAR_H

#include "WinDllMacros.h"
#include <QWidget>

class MainWindow;
class QToolButton;
class QComboBox;

//! The JobActivityStatusBar class is a narrow status bar at very bottom of JobView to switch
//! between activities. Added to the status bar of MainWindow when JobView is shown.

class BA_CORE_API_ JobActivityStatusBar : public QWidget
{
    Q_OBJECT
public:
    JobActivityStatusBar(MainWindow* mainWindow);

signals:
    void toggleJobSelectorRequest();
    void changeActivityRequest(int);
    void dockMenuRequest();

public slots:
    void onActivityChanged(int activity);

private:
    void initAppearance();

    QToolButton* m_toggleJobListButton;
    QComboBox* m_activityCombo;
    QToolButton* m_dockMenuButton;
    MainWindow* m_mainWindow;
};

#endif // JOBACTIVITYSTATUSBAR_H
