// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      FitKernel/inc/ROOTMultiMinMinimizer.h
//! @brief     Defines class ROOTMultiMinMinimizer.
//!
//! @homepage  http://bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef ROOTMULTIMINMINIMIZER_H
#define ROOTMULTIMINMINIMIZER_H

#include "ROOTMinimizer.h"
#include "Math/GSLMinimizer.h"

//! @class ROOTMultiMinMinimizer
//! @ingroup fitting_internal
//! @brief Wrapper for GSL gradiend descent minimizer family

class ROOTMultiMinMinimizer : public ROOTMinimizer
{
public:
    ROOTMultiMinMinimizer(const std::string& minimizer_name, const std::string& algo_type);
    virtual ~ROOTMultiMinMinimizer(){}

protected:
   virtual void propagateOptions();

   ROOT::Math::GSLMinimizer *m_gsl_minimizer;

};


#endif // ROOTMULTIMINMINIMIZER_H
