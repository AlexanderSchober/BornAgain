// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Simulation/ISimulation.h
//! @brief     Defines and implements interface class ISimulation.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef ISIMULATION_H
#define ISIMULATION_H

#include "ICloneable.h"
#include <string>

//! Pure virtual base class, encapsulating different simulations.
//! @ingroup algorithms_internal

class BA_CORE_API_ ISimulation : public ICloneable
{
public:
    enum ESimulationStatus { IDLE, RUNNING, COMPLETED, FAILED };

    ISimulation() : m_status(IDLE) {}

    virtual ~ISimulation() {}

    ISimulation* clone() const =0;

    virtual void run() {}

    bool isCompleted() const { return m_status == COMPLETED; }

    std::string getRunMessage() const { return m_run_message; }

protected:
    virtual void runProtected() {}

    void setStatus(ESimulationStatus status) { m_status = status; }

    void setRunMessage(const std::string& message) { m_run_message = message; }

    ESimulationStatus m_status;
    std::string m_run_message;
};

#endif // ISIMULATION_H
