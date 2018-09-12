// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/SampleDesigner/SampleViewDocks.h
//! @brief     Defines class SampleViewDocks
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef SAMPLEVIEWDOCKS_H
#define SAMPLEVIEWDOCKS_H

#include "DocksController.h"

class SampleView;

//! Holds all docked widgets for SampleView.

class BA_CORE_API_ SampleViewDocks : public DocksController
{
    Q_OBJECT

public:
    SampleViewDocks(SampleView* parent = nullptr);
};

#endif
