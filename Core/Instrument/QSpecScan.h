// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Instrument/QSpecScan.h
//! @brief     Declares QSpecScan class.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef QSPECSCAN_H
#define QSPECSCAN_H

#include "ISpecularScan.h"
#include <memory>

class ScanResolution;

//! Scan type with z-components of scattering vector
//! as coordinate values. Wavelength and incident angles
//! are not accessible separately.

class BA_CORE_API_ QSpecScan : public ISpecularScan
{
public:
    //! Accepts qz-value vector (in inverse nm)
    QSpecScan(std::vector<double> qs_nm);
    QSpecScan(const IAxis& qs_nm);
    //! Sets q-defined specular scan. Accepts either numpy array of q-values sorted in ascending
    //! order or an IAxis object with q-values. Alternatively an axis can be defined in-place, then
    //! the first passed parameter is the number of bins, second - minimum on-axis q-value,
    //! third - maximum on-axis q_value.
    QSpecScan(int nbins, double qz_min, double qz_max);

    ~QSpecScan() override;
    QSpecScan* clone() const override;

#ifndef SWIG
    //! Generates simulation elements for specular simulations
    std::vector<SpecularSimulationElement> generateSimulationElements() const override;

    //! Returns coordinate axis assigned to the data holder
    virtual const IAxis* coordinateAxis() const override {return m_qs.get();}

    //! Returns IFootprintFactor object pointer
    virtual const IFootprintFactor* footprintFactor() const override { return nullptr; }

    //! Returns footprint correction factor for a range of simulation elements of size _n_elements_
    //! and starting from element with index _i_.
    std::vector<double> footprint(size_t i, size_t n_elements) const override;

    //! Returns the number of simulation elements
    size_t numberOfSimulationElements() const override;

    //! Print scan definition in python format
    std::string print() const override;
#endif //SWIG

    //! Sets q resolution values via ScanResolution object.
    //! Limits of the scan resolution will be overriden to
    //! allow for positive q values only.
    void setQResolution(const ScanResolution& resolution);

private:
    void checkInitialization();
    std::unique_ptr<IAxis> m_qs;
    std::unique_ptr<ScanResolution> m_resolution;
};

#endif // QSPECSCAN_H
