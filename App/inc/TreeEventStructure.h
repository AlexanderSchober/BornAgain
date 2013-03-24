// ************************************************************************** //
//                                                                           
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      App/TreeEventStructure.h 
//! @brief     Defines class TreeEventStructure.
//
//! Homepage:  apps.jcns.fz-juelich.de/BornAgain
//! License:   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke 
//
// ************************************************************************** //

#ifndef TREEEVENTSTRUCTURE_H
#define TREEEVENTSTRUCTURE_H

#include "TObject.h"
#include <vector>
#include <string>

//! Data structure respresenting OutputData and mesocrystal settings.

//! For writing/reading in/from the ROOT tree.
//!
class TreeEventOutputData
{
public:
    TreeEventOutputData();
    virtual ~TreeEventOutputData() { }

    void clear();

    int nframe; // number of frame
    double alpha_i; // alpha_i
    double phi_i; // phi_i;

    int nphi_f; // number of phi_f bins in the frame
    double phi_f_min; // minimum value of phi_f
    double phi_f_max; // maximu value of phi_f

    int nalpha_f; // number of alpha_f bins in the frame
    double alpha_f_min; // minimum value of alpha_f
    double alpha_f_max; // maximum value of alpha_f

    double malpha; // rotation of meso around Y
    double mphi; // rotation of meso around Z
    double npR; // size of nano particles inside if meso
    std::vector<std::vector<double > > vi; // frame of measured intensities [phi_f][alpha_f]
    std::vector<std::vector<double > > valpha_f; // values of alpha_f for the frame
    std::vector<std::vector<double > > vphi_f; // values of phi_f for the frames

    ClassDef(TreeEventOutputData,1)
};


//- -------------------------------------------------------------------
//! @class TreeEventFitData
//! @brief Represent fit results after each iteration for writing/reading
//! in/from the ROOT tree
//- -------------------------------------------------------------------
class TreeEventFitData
{
public:
    TreeEventFitData();
    virtual ~TreeEventFitData()  { }
    void clear();

    int niter; // number of iteration
    int nstrategy; // number of strategy
    std::vector<std::vector<double > > real_data; // real data
    std::vector<std::vector<double > > fit_data; // current fit iteration data
    //std::vector<std::vector<double > > diff; // chi2 difference between real and fit data
    std::vector<std::vector<double > > axis0; // values of phi_f (made in 2D for convenient drawing)
    std::vector<std::vector<double > > axis1; // values of alpha_f (made in 2D for convenient drawing)
    double chi2; // current value of the function to minimize
    std::vector<double> parvalues; // vector of minimization parameters
    std::vector<std::string> parnames; // names of parameters
    std::vector<bool> parfixed; // contains fixed flag for parameters

    ClassDef(TreeEventFitData,1)
};

#endif // TREEEVENTSTRUCTURE_H
