// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Simulation/SpecularDataHandler.h
//! @brief     Declares SpecularDataHandler class tree.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef SPECULARDATAHANDLER_H
#define SPECULARDATAHANDLER_H

#include "ICloneable.h"

#include <memory>
#include <vector>

class IAxis;
class IFootprintFactor;
class SpecularSimulationElement;

enum class SPECULAR_DATA_TYPE {angle, lambda, q};

class ISpecularScan : public ICloneable
{
public:
    ISpecularScan(SPECULAR_DATA_TYPE data_type);
    ~ISpecularScan() override;
    ISpecularScan* clone() const override = 0;

    //! Generates simulation elements for specular simulations
    virtual std::vector<SpecularSimulationElement> generateSimulationElements() const = 0;

    //! Returns coordinate axis assigned to the data holder
    virtual const IAxis* coordinateAxis() const = 0;

    //! Returns IFootprintFactor object pointer
    virtual const IFootprintFactor* footprintFactor() const = 0;

    //! Returns footprint correction factor for simulation element with index _i_
    virtual double footprint(size_t i) const = 0;

    //! Returns the number of simulation elements
    virtual size_t numberOfSimulationElements() const = 0;

    SPECULAR_DATA_TYPE dataType() const {return m_data_type;}

private:
    SPECULAR_DATA_TYPE m_data_type;
};

class AngularSpecScan : public ISpecularScan
{
public:
    AngularSpecScan(double wl, std::unique_ptr<IAxis> inc_angle,
                           const IFootprintFactor* footprint = nullptr);
    ~AngularSpecScan() override;
    AngularSpecScan* clone() const override;

    //! Generates simulation elements for specular simulations
    std::vector<SpecularSimulationElement> generateSimulationElements() const override;

    //! Returns coordinate axis assigned to the data holder
    virtual const IAxis* coordinateAxis() const override {return m_inc_angle.get();}

    //! Returns IFootprintFactor object pointer
    virtual const IFootprintFactor* footprintFactor() const override {return m_footprint.get();}

    //! Returns footprint correction factor for simulation element with index _i_
    double footprint(size_t i) const override;

    //! Returns the number of simulation elements
    size_t numberOfSimulationElements() const override;

    double wavelength() const {return m_wl;}

private:
    double m_wl;
    std::unique_ptr<IAxis> m_inc_angle;
    std::unique_ptr<IFootprintFactor> m_footprint;
};

class SpecularDataHandlerTOF : public ISpecularScan
{
public:
    SpecularDataHandlerTOF(double inc_angle, std::unique_ptr<IAxis> qz,
                           const IFootprintFactor* footprint = nullptr);
    ~SpecularDataHandlerTOF() override;
    SpecularDataHandlerTOF* clone() const override;

    //! Generates simulation elements for specular simulations
    std::vector<SpecularSimulationElement> generateSimulationElements() const override;

    //! Returns coordinate axis assigned to the data holder
    virtual const IAxis* coordinateAxis() const override {return m_qs.get();}

    //! Returns IFootprintFactor object pointer
    virtual const IFootprintFactor* footprintFactor() const override {return m_footprint.get();}

    //! Returns footprint correction factor for simulation element with index _i_
    double footprint(size_t i) const override;

    //! Returns the number of simulation elements
    size_t numberOfSimulationElements() const override;

    double inclinationAngle() const {return m_inc_angle;}

private:
    double m_inc_angle;
    std::unique_ptr<IAxis> m_qs;
    std::unique_ptr<IFootprintFactor> m_footprint;
};

class QSpecScan : public ISpecularScan
{
public:
    //! Accepts qz-value vector (in inverse nm)
    QSpecScan(std::unique_ptr<IAxis> qs_nm);
    ~QSpecScan() override;
    QSpecScan* clone() const override;

    //! Generates simulation elements for specular simulations
    std::vector<SpecularSimulationElement> generateSimulationElements() const override;

    //! Returns coordinate axis assigned to the data holder
    virtual const IAxis* coordinateAxis() const override {return m_qs.get();}

    //! Returns IFootprintFactor object pointer
    virtual const IFootprintFactor* footprintFactor() const override { return nullptr; }

    //! Returns footprint correction factor for simulation element with index _i_
    double footprint(size_t) const override { return 1.0; }

    //! Returns the number of simulation elements
    size_t numberOfSimulationElements() const override;

private:
    std::unique_ptr<IAxis> m_qs;
};
#endif // SPECULARDATAHANDLER_H
