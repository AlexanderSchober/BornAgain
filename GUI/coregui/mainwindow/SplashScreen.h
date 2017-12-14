// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/mainwindow/SplashScreen.h
//! @brief     Defines class SplashScreen
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#ifndef SPLASHSCREEN_H
#define SPLASHSCREEN_H

#include "WinDllMacros.h"
#include <QSplashScreen>

class BA_CORE_API_ SplashScreen : public QSplashScreen
{
    Q_OBJECT
public:
    explicit SplashScreen(QWidget* parent = nullptr);

    void start(int show_during = 1500);

public slots:
    void setProgress(int value);

protected:
    void drawContents(QPainter* painter);

private:
    int m_percentage_done;
};

#endif // SPLASHSCREEN_H
