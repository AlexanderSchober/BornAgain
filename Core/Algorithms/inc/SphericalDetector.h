// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Algorithms/inc/SphericalDetector.h
//! @brief     Defines class SphericalDetector.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef SPHERICALDETECTOR_H_
#define SPHERICALDETECTOR_H_

#include "IDetector2D.h"
#include "IDetectorResolution.h"
#include "SafePointerVector.h"
#include "EigenCore.h"
#include "DetectorMask.h"
#include "SimulationElement.h"
#include "Beam.h"
#include "IPixelMap.h"

class AngularPixelMap;

//! @class SphericalDetector
//! @ingroup simulation
//! @brief A spherical detector with axes and resolution function.

class BA_CORE_API_ SphericalDetector : public IDetector2D
{
public:
    SphericalDetector();
    SphericalDetector(const SphericalDetector &other);
    SphericalDetector &operator=(const SphericalDetector &other);

    virtual SphericalDetector* clone() const;

    virtual ~SphericalDetector() {}

    //! Adds parameters from local pool to external pool and call recursion over direct children.
    virtual std::string addParametersToExternalPool(std::string path, ParameterPool *external_pool,
                                                    int copy_number = -1) const;

protected:
    //! Create an IPixelMap for the given OutputData object and index
    virtual IPixelMap* createPixelMap(size_t index) const;

    virtual void print(std::ostream &ostr) const;

    //! Registers some class members for later access via parameter pool.
    virtual void init_parameters() {}

    //! Returns the name for the axis with given index
    virtual std::string getAxisName(size_t index) const;
};

class AngularPixelMap : public IPixelMap
{
public:
    AngularPixelMap(Bin1D alpha_bin, Bin1D phi_bin);
    virtual ~AngularPixelMap() {}

    virtual AngularPixelMap* clone() const;
    virtual AngularPixelMap* createZeroSizeMap(double x, double y) const;
    virtual kvector_t getK(double x, double y, double wavelength) const;
    virtual double getIntegrationFactor(double x, double y) const;
    virtual double getSolidAngle() const;
private:
    double m_alpha, m_phi;
    double m_dalpha, m_dphi;
    double m_solid_angle;
};

#endif /* SPHERICALDETECTOR_H_ */
