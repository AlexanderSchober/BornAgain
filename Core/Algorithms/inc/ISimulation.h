#ifndef ISIMULATION_H
#define ISIMULATION_H
// ********************************************************************
// * The BornAgain project                                            *
// * Simulation of neutron and x-ray scattering at grazing incidence  *
// *                                                                  *
// * LICENSE AND DISCLAIMER                                           *
// * Lorem ipsum dolor sit amet, consectetur adipiscing elit.  Mauris *
// * eget quam orci. Quisque  porta  varius  dui,  quis  posuere nibh *
// * mollis quis. Mauris commodo rhoncus porttitor.                   *
// ********************************************************************
//! @file   ISimulation.h
//! @brief  Definition of ISimulation class
//! @author Scientific Computing Group at FRM II
//! @date   01.04.2012

#include "ICloneable.h"

class ISimulation : public ICloneable
{
public:
    virtual ~ISimulation() { }
    ISimulation *clone() const { throw NotImplementedException("ISimulation::clone() -> Error: not implemented exception."); }
    virtual void run() { }
};

#endif // ISIMULATION_H
