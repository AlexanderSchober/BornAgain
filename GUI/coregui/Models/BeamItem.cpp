// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Models/BeamItem.cpp
//! @brief     Implements class BeamItem
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "BeamItem.h"
#include "InterferenceFunctionItems.h"
#include "ComboProperty.h"
#include "AngleProperty.h"
#include "DistributionItem.h"
#include "ScientificDoubleProperty.h"
#include "BeamDistributionItem.h"
#include "Units.h"
#include "BeamDistributionItem.h"
#include <QDebug>


// ---------------


//const QString BeamWavelengthItem::P_DISTRIBUTION = "Distribution";
//const QString BeamWavelengthItem::P_CACHED_VALUE = "Value";

//BeamWavelengthItem::BeamWavelengthItem(ParameterizedItem *parent)
//    : ParameterizedItem(Constants::BeamWavelengthType, parent)
//{
//    setItemName(Constants::BeamWavelengthType);
//    registerProperty(P_CACHED_VALUE, 0.1, PropertyAttribute(PropertyAttribute::HIDDEN, AttLimits::lowerLimited(1e-4), 4));
//    registerGroupProperty(P_DISTRIBUTION, Constants::DistributionExtendedGroup);
//    setGroupProperty(P_DISTRIBUTION, Constants::DistributionNoneType);
//}

////! updates new DistributionItem with cached_value
//void BeamWavelengthItem::onSubItemChanged(const QString &propertyName)
//{
//    qDebug() << "BeamWavelengthItem::onSubItemChanged(const QString &propertyName)" << propertyName;
//    if(propertyName == P_DISTRIBUTION) {
//        DistributionItem *distribution = dynamic_cast<DistributionItem *>(getSubItems()[P_DISTRIBUTION]);
//        Q_ASSERT(distribution);
//        double cached_value = getRegisteredProperty(P_CACHED_VALUE).toDouble();
//        PropertyAttribute cached_attribute = getPropertyAttribute(P_CACHED_VALUE);
//        cached_attribute.setAppearance(PropertyAttribute::VISIBLE);
//        distribution->init_parameters(cached_value, cached_attribute);
//    }
//    ParameterizedItem::onSubItemChanged(propertyName);
//}

//void BeamWavelengthItem::onSubItemPropertyChanged(const QString &property_group, const QString &property_name)
//{
//    qDebug() << "BeamWavelengthItem::onSubItemPropertyChanged(const QString &property_group, const QString &property_name)" << property_group << property_name;
//    if(property_group == P_DISTRIBUTION && property_name == DistributionNoneItem::P_VALUE) {
//        double value_to_cache = getSubItems()[P_DISTRIBUTION]->getRegisteredProperty(DistributionNoneItem::P_VALUE).toDouble();
//        setRegisteredProperty(P_CACHED_VALUE, value_to_cache);
//    }
//    ParameterizedItem::onSubItemPropertyChanged(property_group, property_name);
//}


// ------------ BeamAngleItem ---

//const QString BeamAngleItem::P_DISTRIBUTION = "Distribution";
//const QString BeamAngleItem::P_CACHED_VALUE = "Value";

//BeamAngleItem::BeamAngleItem(ParameterizedItem *parent)
//    : ParameterizedItem(Constants::BeamAngleType, parent)
//{
//    setItemName(Constants::BeamAngleType);
//    registerProperty(P_CACHED_VALUE, 0.1, PropertyAttribute(PropertyAttribute::HIDDEN, AttLimits::limitless(), 2));
//    registerGroupProperty(P_DISTRIBUTION, Constants::DistributionExtendedGroup);
//    setGroupProperty(P_DISTRIBUTION, Constants::DistributionNoneType);
//}

//void BeamAngleItem::onPropertyChange(const QString &name)
//{
//    if(name == P_CACHED_VALUE) {
//        DistributionItem *distribution = dynamic_cast<DistributionItem *>(getSubItems()[P_DISTRIBUTION]);
//        if(distribution) {
//            double cached_value = getRegisteredProperty(P_CACHED_VALUE).toDouble();
//            PropertyAttribute cached_attribute = getPropertyAttribute(P_CACHED_VALUE);
//            cached_attribute.setAppearance(PropertyAttribute::VISIBLE);
//            distribution->init_parameters(cached_value, cached_attribute);
//        }
//    }
//}

////! updates new DistributionItem with cached_value
//void BeamAngleItem::onSubItemChanged(const QString &propertyName)
//{
//    qDebug() << "BeamAngleItem::onSubItemChanged(const QString &propertyName)" << propertyName;
//    if(propertyName == P_DISTRIBUTION) {
//        DistributionItem *distribution = dynamic_cast<DistributionItem *>(getSubItems()[P_DISTRIBUTION]);
//        Q_ASSERT(distribution);
//        double cached_value = getRegisteredProperty(P_CACHED_VALUE).toDouble();
//        PropertyAttribute cached_attribute = getPropertyAttribute(P_CACHED_VALUE);
//        cached_attribute.setAppearance(PropertyAttribute::VISIBLE);
//        distribution->init_parameters(cached_value, cached_attribute);
//    }
//    ParameterizedItem::onSubItemChanged(propertyName);
//}

//void BeamAngleItem::onSubItemPropertyChanged(const QString &property_group, const QString &property_name)
//{
//    qDebug() << "BeamAngleItem::onSubItemPropertyChanged(const QString &property_group, const QString &property_name)" << property_group << property_name;
//    if(property_group == P_DISTRIBUTION && property_name == DistributionNoneItem::P_VALUE) {
//        double value_to_cache = getSubItems()[P_DISTRIBUTION]->getRegisteredProperty(DistributionNoneItem::P_VALUE).toDouble();
//        setRegisteredProperty(P_CACHED_VALUE, value_to_cache);
//    }
//    ParameterizedItem::onSubItemPropertyChanged(property_group, property_name);
//}



const QString TestBeamItem::P_INTENSITY = "Intensity [1/s]";
const QString TestBeamItem::P_WAVELENGTH = "Wavelength";
const QString TestBeamItem::P_INCLINATION_ANGLE = "Inclination Angle";
const QString TestBeamItem::P_AZIMUTHAL_ANGLE = "Azimuthal Angle";

TestBeamItem::TestBeamItem(ParameterizedItem *parent)
    : ParameterizedItem(Constants::BeamType, parent)
{
    ScientificDoubleProperty intensity(1e+08);
    registerProperty(P_INTENSITY, intensity.getVariant(), PropertyAttribute(AttLimits::lowerLimited(0.0)));

    ParameterizedItem *item = registerGroupProperty(P_WAVELENGTH, Constants::BeamDistributionType);
    BeamDistributionItem *distributionItem = dynamic_cast<BeamDistributionItem *>(item);
    distributionItem->setInitialValue(0.1, PropertyAttribute(PropertyAttribute::HIDDEN, AttLimits::lowerLimited(1e-4), 4));

    item = registerGroupProperty(P_INCLINATION_ANGLE, Constants::BeamDistributionType);
    distributionItem = dynamic_cast<BeamDistributionItem *>(item);
    distributionItem->setInitialValue(0.2, PropertyAttribute(PropertyAttribute::HIDDEN, AttLimits::limited(0.0, 90.0), 2));

    item = registerGroupProperty(P_AZIMUTHAL_ANGLE, Constants::BeamDistributionType);
    distributionItem = dynamic_cast<BeamDistributionItem *>(item);
    distributionItem->setInitialValue(0.0, PropertyAttribute(PropertyAttribute::HIDDEN, AttLimits::limited(-90.0, 90.0), 2));
}

double TestBeamItem::getIntensity() const
{
    ScientificDoubleProperty intensity = getRegisteredProperty(P_INTENSITY).value<ScientificDoubleProperty>();
    return intensity.getValue();
}

void TestBeamItem::setIntensity(double value)
{
    ScientificDoubleProperty intensity = getRegisteredProperty(P_INTENSITY).value<ScientificDoubleProperty>();
    intensity.setValue(value);
    setRegisteredProperty(P_INTENSITY, intensity.getVariant());
}

double TestBeamItem::getWavelength() const
{
    ParameterizedItem *beamWavelength = getSubItems()[P_WAVELENGTH];
    Q_ASSERT(beamWavelength);
    return beamWavelength->getRegisteredProperty(BeamDistributionItem::P_CACHED_VALUE).toDouble();
}

void TestBeamItem::setWavelength(double value, const QString &distribution_name)
{
    Q_UNUSED(distribution_name);
    ParameterizedItem *beamWavelength = getSubItems()[P_WAVELENGTH];
    Q_ASSERT(beamWavelength);
    ParameterizedItem *distributionItem = beamWavelength->setGroupProperty(BeamDistributionItem::P_DISTRIBUTION, Constants::DistributionNoneType);
    Q_ASSERT(distributionItem);
    distributionItem->setRegisteredProperty(DistributionNoneItem::P_VALUE, value);
}

double TestBeamItem::getInclinationAngle() const
{
    ParameterizedItem *angleItem = getSubItems()[P_INCLINATION_ANGLE];
    Q_ASSERT(angleItem);
    return angleItem->getRegisteredProperty(BeamDistributionItem::P_CACHED_VALUE).toDouble();
}

void TestBeamItem::setInclinationAngle(double value, const QString &distribution_name)
{
    Q_UNUSED(distribution_name);
    ParameterizedItem *angleItem = getSubItems()[P_INCLINATION_ANGLE];
    Q_ASSERT(angleItem);
    ParameterizedItem *distributionItem = angleItem->setGroupProperty(BeamDistributionItem::P_DISTRIBUTION, Constants::DistributionNoneType);
    Q_ASSERT(distributionItem);
    distributionItem->setRegisteredProperty(DistributionNoneItem::P_VALUE, value);
}

double TestBeamItem::getAzimuthalAngle() const
{
    ParameterizedItem *angleItem = getSubItems()[P_AZIMUTHAL_ANGLE];
    Q_ASSERT(angleItem);
    return angleItem->getRegisteredProperty(BeamDistributionItem::P_CACHED_VALUE).toDouble();
}

void TestBeamItem::setAzimuthalAngle(double value, const QString &distribution_name)
{
    Q_UNUSED(distribution_name);
    ParameterizedItem *angleItem = getSubItems()[P_AZIMUTHAL_ANGLE];
    Q_ASSERT(angleItem);
    ParameterizedItem *distributionItem = angleItem->setGroupProperty(BeamDistributionItem::P_DISTRIBUTION, Constants::DistributionNoneType);
    Q_ASSERT(distributionItem);
    distributionItem->setRegisteredProperty(DistributionNoneItem::P_VALUE, value);
}

