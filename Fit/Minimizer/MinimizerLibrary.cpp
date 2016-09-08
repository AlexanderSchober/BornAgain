// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Fit/Minimizer/MinimizerLibrary.cpp
//! @brief     Implements namespace MinimizerLibrary.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "MinimizerLibrary.h"
#include "AlgorithmNames.h"
#include <stdexcept>

using namespace MinimizerLibrary;

AlgorithmInfo::AlgorithmInfo(const std::string& algType, const std::string& algDescription)
    : InfoItem(algType, algDescription)
{
}

MinimizerInfo::MinimizerInfo(const std::string& minimizerType,
                             const std::string& minimizerDescription)
    : InfoItem(minimizerType, minimizerDescription)
{
}

void MinimizerInfo::addAlgorithm(const MinimizerLibrary::AlgorithmInfo& algorithm)
{
    m_algorithms.push_back(algorithm);
}

void MinimizerInfo::addAlgorithm(const std::string& algorithmName,
                                 const std::string& algorithmDescription)
{
    addAlgorithm(AlgorithmInfo(algorithmName, algorithmDescription));
}

//! Return list of algorithm types.

std::list<std::string> MinimizerInfo::algorithmTypes() const
{
    std::list<std::string> result;
    for(AlgorithmInfo algo : m_algorithms)
        result.push_back(algo.getType());
    return result;
}

//! Returns list of string with description of all available algorithms.

std::list<std::string> MinimizerInfo::algorithmDescriptions() const
{
    std::list<std::string> result;
    for(AlgorithmInfo algo : m_algorithms)
        result.push_back(algo.getDescription());
    return result;
}

//! Catalogue constructor fills in all information related to available minimizers/algorithms.
// FIXME Don't forget "SpeestDescent"

Catalogue::Catalogue()
{
    MinimizerInfo minuit(
        ObsoleteMinimizerNames::Minuit,
        "Minuit2 minimizer from ROOT library");
    minuit.addAlgorithm(
        ObsoleteAlgorithmNames::Migrad,
        "Variable-metric method with inexact line search, best minimizer according to ROOT.");
    minuit.addAlgorithm(
        ObsoleteAlgorithmNames::Simplex,
        "Simplex method of Nelder and Meadh, "
        "robust against big fluctuations in objective function.");
    minuit.addAlgorithm(
        ObsoleteAlgorithmNames::Combined,
        "Combination of Migrad and Simplex (if Migrad fails).");
    minuit.addAlgorithm(
        ObsoleteAlgorithmNames::Scan,
        "Simple objective function scan, one parameter at a time.");
    minuit.addAlgorithm(
        ObsoleteAlgorithmNames::Fumili,
        "Gradient descent minimizer similar to Levenberg-Margquardt, "
        "sometimes can be better than all others.");
    addMinimizer(minuit);

    MinimizerInfo gsl(
        ObsoleteMinimizerNames::GSL,
        "Set of minimizers from GNU Scientific Library");
    gsl.addAlgorithm(
        ObsoleteAlgorithmNames::ConjugateFR,
        "Fletcher-Reeves conjugate gradient");
    gsl.addAlgorithm(
        ObsoleteAlgorithmNames::ConjugatePR,
        "Polak-Ribiere conjugate gradient");
    gsl.addAlgorithm(
        ObsoleteAlgorithmNames::BFGS,
        "BFGS conjugate gradient");
    gsl.addAlgorithm(
        ObsoleteAlgorithmNames::BFGS2,
        "BFGS conjugate gradient (Version 2)");
    gsl.addAlgorithm(
        ObsoleteAlgorithmNames::LMA,
        "Levenberg-Marquardt, often works quite well.");
//    gsl.addAlgorithm(AlgorithmNames::SimAn, "Simulated Annealing");
    addMinimizer(gsl);

    MinimizerInfo genetic(
        ObsoleteMinimizerNames::Genetic,
        "TMVA Genetic Algorithm");
    genetic.addAlgorithm(
        ObsoleteAlgorithmNames::Genetic,
        "TMVA Genetic Algorithm");
    addMinimizer(genetic);
}

//! Adds minimizer info to the catalogue.

void Catalogue::addMinimizer(const MinimizerInfo& minimizer)
{
    if(m_minimizers.find(minimizer.getType())!=m_minimizers.end())
        throw std::runtime_error(
            "BUG in Catalogue::addMinimizer() -> Error. "
            "Attempt to add twice minimizer '" + minimizer.getType() + "'");
    m_minimizers[minimizer.getType()] = minimizer;
}

//! Returns list of algorithm types for given minimizer type.

std::list<std::string> Catalogue::algorithmTypes(const std::string& minimizerType)
{
    return minimizerInfo(minimizerType).algorithmTypes();
}

//! Returns list of algorithm descriptions for given minimizer type.

std::list<std::string> Catalogue::algorithmDescriptions(const std::string& minimizerType)
{
    return  minimizerInfo(minimizerType).algorithmDescriptions();
}

//! Returns minimizer info for given minimizer type.

MinimizerLibrary::MinimizerInfo Catalogue::minimizerInfo(const std::string& minimizerType)
{
    auto it = m_minimizers.find(minimizerType);
    if(it == m_minimizers.end())
        throw std::runtime_error(
            "Catalogue::addMinimizer() -> Error. Non existing minimizer " + minimizerType);
    return m_minimizers[minimizerType];
}
