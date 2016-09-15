// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Fit/Minimizer/ObjectiveFunction.h
//! @brief     Declares class ObjectiveFunction
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "ObjectiveFunction.h"
#include <stdexcept>

ObjectiveFunction::ObjectiveFunction()
    : m_ncalls(0)
    , m_ndatasize(0)
{

}

void ObjectiveFunction::setObjectiveFunction(objective_function_t func)
{
    m_objective_function = func;
}

void ObjectiveFunction::setGradientFunction(gradient_function_t func, int ndatasize)
{
    m_gradient_function = func;
    m_ndatasize = ndatasize;
}

//! Evaluates the value of the function for given vector of function parameters using
//! callback mechanism.

double ObjectiveFunction::evaluate(const std::vector<double> &pars)
{
    if(!m_objective_function)
        throw std::runtime_error("ObjectiveFunction::evaluate() -> Error. "
                                 "Objective function is not set");

    ++m_ncalls;
    return m_objective_function(pars);
}

double ObjectiveFunction::evaluate_gradient(const std::vector<double>& pars, int index,
                                            std::vector<double> &gradient)
{
    if(!m_gradient_function)
        throw std::runtime_error("ObjectiveFunction::evaluate() -> Error. "
                                 "Gradient function is not set");

    return m_gradient_function(pars, index, gradient);
}

//double ObjectiveFunction::evaluate_gradient(const std::vector<double> &pars, int index, std::vector<double> &gradient)
//{
//    if(!m_gradient_function)
//        throw std::runtime_error("ObjectiveFunction::evaluate() -> Error. "
//                                 "Gradient function is not set");

//    return m_gradient_function(pars, index, gradient);
//}
