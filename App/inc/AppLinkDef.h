// ************************************************************************** //
//                                                                           
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      App/inc/AppLinkDef.h 
//! @brief     A few link pragmas.
//
//! Homepage:  apps.jcns.fz-juelich.de/BornAgain
//! License:   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke 
//
// ************************************************************************** //

#include "App.h"
#ifdef __CINT__

#pragma link off all globals;
#pragma link off all classes;
#pragma link off all functions;

#pragma link C++ class DrawHelper+;
#pragma link C++ class TreeEventOutputData+;
#pragma link C++ class TreeEventFitData+;

#endif
