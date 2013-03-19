// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Algorithms/inc/Instrument.h
//! @brief     Defines class Instrument.
//!
//! @homepage  apps.jcns.fz-juelich.de/BornAgain
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke 
//
// ************************************************************************** //

#ifndef INSTRUMENT_H_
#define INSTRUMENT_H_

#include "Beam.h"
#include "Detector.h"
#include "IResolutionFunction2D.h"

//! Assembles beam, detector and their relative positions wrt the sample.

class Instrument : public IParameterized
{
public:
    Instrument();
    Instrument(const Instrument &other);

    ~Instrument() {}

    //! get the beam data
    Beam getBeam() const;

    //! set the beam data
    void setBeam(Beam beam);

    //! set the beam wavelength and incoming angles
    void setBeamParameters(double lambda, double alpha_i, double phi_i);

    //! set the beam's intensity
    void setBeamIntensity(double intensity) { m_beam.setIntensity(intensity); }

    //! get the beam's intensity
    double getIntensity() const { return m_beam.getIntensity(); }

    //! get the detector data
    Detector getDetector() const;

    //! get a detector axis
    const IAxis &getDetectorAxis(size_t index) const;

    //! get the detector's dimension
    size_t getDetectorDimension() const { return m_detector.getDimension(); }

    //! set detector parameters using axes of output data
    void matchDetectorParameters(const OutputData<double > &output_data);

    //! set detector parameters using angle ranges
    void setDetectorParameters(size_t n_phi, double phi_f_min, double phi_f_max,
            size_t n_alpha, double alpha_f_min, double alpha_f_max, bool isgisaxs_style=false);

    //! set detector parameters using parameter object
    void setDetectorParameters(const DetectorParameters &params);

    //! set detector resolution function
    void setDetectorResolutionFunction(IResolutionFunction2D *p_resolution_function);

    //! apply the detector resolution to the given intensity map
    void applyDetectorResolution(OutputData<double> *p_intensity_map) const;

    //! add parameters from local pool to external pool and call recursion over direct children
    virtual std::string addParametersToExternalPool(std::string path, ParameterPool *external_pool, int copy_number=-1) const;

    //! normalize a detector image
    void normalize(OutputData<double> *p_intensity) const;

protected:
    //! initialize pool parameters, i.e. register some of class members for later access via parameter pool
    virtual void init_parameters();

    Detector m_detector;
    Beam m_beam;
};

inline Beam Instrument::getBeam() const
{
    return m_beam;
}

inline void Instrument::setBeam(Beam beam)
{
    m_beam = beam;
}

inline void Instrument::setBeamParameters(double lambda, double alpha_i, double phi_i)
{
    m_beam.setCentralK(lambda, alpha_i, phi_i);
}

inline Detector Instrument::getDetector() const
{
    return m_detector;
}

inline const IAxis &Instrument::getDetectorAxis(size_t index) const
{
    return m_detector.getAxis(index);
}

#endif /* INSTRUMENT_H_ */
