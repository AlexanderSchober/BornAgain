// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      FitKernel/src/ROOTMultiFitMinimizer.cpp
//! @brief     Implements class ROOTMultiFitMinimizer.
//
//! Homepage:  apps.jcns.fz-juelich.de/BornAgain
//! License:   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "ROOTLMAMinimizer.h"
#include "Math/GenAlgoOptions.h"


ROOTLMAMinimizer::ROOTLMAMinimizer(const std::string& minimizer_name, const std::string& algo_type)
  : ROOTMinimizer(minimizer_name, algo_type)
{
    m_lma_minimizer = new ROOT::Patch::GSLNLSMinimizer(2);
    m_root_minimizer = m_lma_minimizer;
}

// this function serve as a bridge and propagates MinimizerOptions inside GSLNLSMinimizer
void ROOTLMAMinimizer::propagateOptions()
{
    ROOTMinimizer::propagateOptions();
}

