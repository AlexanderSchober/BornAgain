// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Fitting/FitStrategyAdjustMinimizer.h
//! @brief     Defines class FitStrategyAdjustMinimizer
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef FITSTRATEGYADJUSTMINIMIZER_H
#define FITSTRATEGYADJUSTMINIMIZER_H

#include "IFitStrategy.h"

//! @class FitStrategyAdjustMinimizer
//! @ingroup fitting
//! @brief Strategy modifies mimimizer settings before running minimization round.

class BA_CORE_API_ FitStrategyAdjustMinimizer : public IFitStrategy
{
public:
    FitStrategyAdjustMinimizer();

    FitStrategyAdjustMinimizer(const std::string& minimizerName,
                               const std::string& algorithmName = std::string(),
                               const std::string& optionString=std::string());

    virtual FitStrategyAdjustMinimizer* clone() const;

    void setMinimizer(const std::string& minimizerName,
                      const std::string& algorithmName = std::string(),
                      const std::string& optionString=std::string());

    virtual void execute();

protected:
    virtual std::string toString() const;
    FitStrategyAdjustMinimizer(const FitStrategyAdjustMinimizer &other);

private:
    std::string m_minimizerName;
    std::string m_algorithmName;
    std::string m_optionString;
};

#endif
