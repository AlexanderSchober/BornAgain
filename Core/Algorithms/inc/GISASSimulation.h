// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Algorithms/inc/GISASSimulation.h
//! @brief     Defines class GISASSimulation.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef GISASSIMULATION_H_
#define GISASSIMULATION_H_

#include "ISampleBuilder.h"
#include "Instrument.h"
#include "SimulationParameters.h"
#include "DistributionHandler.h"
#include "ProgressHandler.h"
#include "Simulation.h"

#include "EigenCore.h"

#include <boost/function.hpp>

class ProgramOptions;
class ProgressHandlerDWBA;
class IHistogram;
class Histogram2D;
namespace Geometry {
class IShape2D;
}

//! @class Simulation
//! @ingroup simulation
//! @brief Main class to run the simulation.

class BA_CORE_API_ GISASSimulation : public Simulation
{
public:
    GISASSimulation();
    GISASSimulation(const ProgramOptions *p_options);
    GISASSimulation(const ISample& p_sample, const ProgramOptions *p_options=0);
    GISASSimulation(SampleBuilder_t p_sample_builder,
               const ProgramOptions *p_options=0);
    ~GISASSimulation() {}

    GISASSimulation *clone() const;

    //! Put into a clean state for running a simulation
    virtual void prepareSimulation();

    //! Normalize the detector counts
    void normalize();

    //! Gets the number of elements this simulation needs to calculate
    virtual int getNumberOfSimulationElements() const;

    //! Returns detector intensity map (no detector resolution)
    const OutputData<double>* getOutputData() const { return &m_intensity_map; }

    //! Returns clone of the detector intensity map with detector resolution applied
    OutputData<double>* getDetectorIntensity() const;

    //! Returns clone of the detector intensity map with detector resolution applied in the form
    //! of 2D histogram.
    Histogram2D *getIntensityData() const;

    //! Sets the instrument containing beam and detector information
    void setInstrument(const Instrument& instrument);

    //! Returns the instrument containing beam and detector information
    const Instrument& getInstrument() const { return m_instrument; }

    //! Sets beam parameters from here (forwarded to Instrument)
    void setBeamParameters(double wavelength, double alpha_i, double phi_i);

    //! Sets beam intensity from here (forwarded to Instrument)
    void setBeamIntensity(double intensity);

    //! Sets the beam polarization according to the given Bloch vector
    void setBeamPolarization(const kvector_t& bloch_vector);

    //! Sets the detector (axes can be overwritten later)
    void setDetector(const IDetector2D& detector);

    //! Sets detector parameters using axes of output data
    void setDetectorParameters(const OutputData<double> &output_data);
    void setDetectorParameters(const IHistogram &hisotgram);

    //! Sets detector parameters using angle ranges
    void setDetectorParameters(size_t n_x, double x_min, double x_max,
                               size_t n_y, double y_min, double y_max);

    //! Define resolution function for detector
    void setDetectorResolutionFunction(const IResolutionFunction2D &resolution_function);

    //! Removes detector resolution function
    void removeDetectorResolutionFunction();

    //! Sets the polarization analyzer characteristics of the detector
    void setAnalyzerProperties(const kvector_t &direction, double efficiency,
                               double total_transmission=1.0);

    //! Adds parameters from local to external pool, and call recursion over direct children
    std::string addParametersToExternalPool(std::string path, ParameterPool *external_pool,
                                            int copy_number=-1) const;

    //! returns wavelength
    virtual double getWavelength() const;

    //! removes all masks from the detector
    void removeMasks();

    //! Adds mask of given shape to the stack of detector masks. The mask value 'true' means
    //! that the channel will be excluded from the simulation. The mask which is added last
    //! has priority.
    //! @param shape The shape of mask (Rectangle, Polygon, Line, Ellipse)
    //! @mask_value The value of mask
    void addMask(const Geometry::IShape2D &shape, bool mask_value = true);

    //! Put the mask for all detector channels (i.e. exclude whole detector from the analysis)
    void maskAll();

protected:
    GISASSimulation(const GISASSimulation& other);

    //! Registers some class members for later access via parameter pool
    void init_parameters();

    //! Initializes the vector of Simulation elements
    virtual void initSimulationElementVector();

    //! Creates the appropriate data structure (e.g. 2D intensity map) from the calculated
    //! SimulationElement objects
    virtual void transferResultsToIntensityMap();

    //! Default implementation only adds the detector axes
    void updateIntensityMap();

    // extra components describing a GISAS experiment and its simulation:
    Instrument m_instrument;
    OutputData<double> m_intensity_map;
};

#endif /* GISASSIMULATION_H_ */
