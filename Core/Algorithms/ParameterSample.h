// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Algorithms/inc/ParameterSample.h
//! @brief     Defines class ParameterSample.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef PARAMETERSAMPLE_H_
#define PARAMETERSAMPLE_H_

//! @class ParameterSample
//! @ingroup algorithms_internal
//! @brief Represents a sampled parameter value with its weight
struct ParameterSample
{
	double value;
	double weight;
};

#endif /* PARAMETERSAMPLE_H_ */
