// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/IntensityDataItem.cpp
//! @brief     Implements class IntensityDataItem
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "IntensityDataItem.h"
#include "AxesItems.h"
#include "BornAgainNamespace.h"
#include "ComboProperty.h"
#include "GUIHelpers.h"
#include "MaskItems.h"
#include "ProjectionItems.h"
#include "BornAgainNamespace.h"

namespace {
ComboProperty gradientCombo() {
    ComboProperty result;
    result << Constants::GRADIENT_GRAYSCALE << Constants::GRADIENT_HOT << Constants::GRADIENT_COLD
           << Constants::GRADIENT_NIGHT << Constants::GRADIENT_CANDY
           << Constants::GRADIENT_GEOGRAPHY << Constants::GRADIENT_ION
           << Constants::GRADIENT_THERMAL << Constants::GRADIENT_POLAR
           << Constants::GRADIENT_SPECTRUM << Constants::GRADIENT_JET << Constants::GRADIENT_HUES;
    result.setValue(Constants::GRADIENT_JET);
    return result;
}
}

const QString IntensityDataItem::P_AXES_UNITS = "Axes Units";
const QString IntensityDataItem::P_TITLE = "Title";
const QString IntensityDataItem::P_PROJECTIONS_FLAG = "Projections";
const QString IntensityDataItem::P_IS_INTERPOLATED = "Interpolation";
const QString IntensityDataItem::P_GRADIENT = "Gradient";
const QString IntensityDataItem::P_XAXIS = "x-axis";
const QString IntensityDataItem::P_YAXIS = "y-axis";
const QString IntensityDataItem::P_ZAXIS = "color-axis";
const QString IntensityDataItem::P_FILE_NAME = "FileName";
const QString IntensityDataItem::T_MASKS = "Mask tag";
const QString IntensityDataItem::T_PROJECTIONS = "Projection tag";

IntensityDataItem::IntensityDataItem() : SessionItem(Constants::IntensityDataType)
{
    ComboProperty units = ComboProperty() << Constants::UnitsNbins;
    addProperty(P_AXES_UNITS, units.variant());

    addProperty(P_TITLE, QString())->setVisible(false);

    addProperty(P_PROJECTIONS_FLAG, false)->setVisible(false);
    addProperty(P_IS_INTERPOLATED, true);
    addProperty(P_GRADIENT, gradientCombo().variant());

    SessionItem* item = addGroupProperty(P_XAXIS, Constants::BasicAxisType);
    item->getItem(BasicAxisItem::P_NBINS)->setVisible(false);

    item = addGroupProperty(P_YAXIS, Constants::BasicAxisType);
    item->getItem(BasicAxisItem::P_NBINS)->setVisible(false);

    item = addGroupProperty(P_ZAXIS, Constants::AmplitudeAxisType);
    item->getItem(BasicAxisItem::P_NBINS)->setVisible(false);

    setXaxisTitle("X [nbins]");
    setYaxisTitle("Y [nbins]");

    // name of the file used to serialize given IntensityDataItem
    addProperty(P_FILE_NAME, QStringLiteral("undefined"))->setVisible(false);

    registerTag(T_MASKS, 0, -1, QStringList() << Constants::MaskContainerType);
    setDefaultTag(T_MASKS);

    registerTag(T_PROJECTIONS, 0, -1, QStringList() << Constants::ProjectionContainerType);

    mapper()->setOnPropertyChange([this](const QString& name)
    {
        if(name == P_FILE_NAME)
            setLastModified(QDateTime::currentDateTime());
    });

    mapper()->setOnValueChange([this]()
    {
        // OutputData was modified
        setLastModified(QDateTime::currentDateTime());
    });

}

void IntensityDataItem::setOutputData(OutputData<double>* data)
{
    Q_ASSERT(data);
    m_data.reset(data);

    updateAxesZoomLevel();
    updateAxesLabels();
    updateDataRange();

    emitDataChanged();
}

//! Sets the raw data vector from external source

void IntensityDataItem::setRawDataVector(const OutputData<double>* data)
{
    if (!m_data->hasSameDimensions(*data)) {
        throw GUIHelpers::Error("IntensityDataItem::setRawDataVector() -> Error. "
                                "Different dimensions of data.");
    }
    m_data->setRawDataVector(data->getRawDataVector());
    emitDataChanged();
}

int IntensityDataItem::getNbinsX() const
{
    return xAxisItem()->getItemValue(BasicAxisItem::P_NBINS).toInt();
}

int IntensityDataItem::getNbinsY() const
{
    return yAxisItem()->getItemValue(BasicAxisItem::P_NBINS).toInt();
}

double IntensityDataItem::getLowerX() const
{
    return getItem(P_XAXIS)->getItemValue(BasicAxisItem::P_MIN).toDouble();
}

double IntensityDataItem::getUpperX() const
{
    return getItem(P_XAXIS)->getItemValue(BasicAxisItem::P_MAX).toDouble();
}

double IntensityDataItem::getXmin() const
{
    const double defaultXmin(0.0);
    return m_data ? m_data->getAxis(BornAgain::X_AXIS_INDEX).getMin() : defaultXmin;
}

double IntensityDataItem::getXmax() const
{
    const double defaultXmax(1.0);
    return m_data ? m_data->getAxis(BornAgain::X_AXIS_INDEX).getMax() : defaultXmax;
}

double IntensityDataItem::getLowerY() const
{
    return getItem(P_YAXIS)->getItemValue(BasicAxisItem::P_MIN).toDouble();
}

double IntensityDataItem::getUpperY() const
{
    return getItem(P_YAXIS)->getItemValue(BasicAxisItem::P_MAX).toDouble();
}

double IntensityDataItem::getYmin() const
{
    const double defaultYmin(0.0);
    return m_data ? m_data->getAxis(BornAgain::Y_AXIS_INDEX).getMin() : defaultYmin;
}

double IntensityDataItem::getYmax() const
{
    const double defaultYmax(1.0);
    return m_data ? m_data->getAxis(BornAgain::Y_AXIS_INDEX).getMax() : defaultYmax;
}

double IntensityDataItem::getLowerZ() const
{
    return getItem(P_ZAXIS)->getItemValue(BasicAxisItem::P_MIN).toDouble();
}

double IntensityDataItem::getUpperZ() const
{
    return getItem(P_ZAXIS)->getItemValue(BasicAxisItem::P_MAX).toDouble();
}

QString IntensityDataItem::getGradient() const
{
    ComboProperty combo_property = getItemValue(P_GRADIENT).value<ComboProperty>();
    return combo_property.getValue();
}

bool IntensityDataItem::isLogz() const
{
    return getItem(P_ZAXIS)->getItemValue(AmplitudeAxisItem::P_IS_LOGSCALE).toBool();
}

bool IntensityDataItem::isInterpolated() const
{
    return getItemValue(P_IS_INTERPOLATED).toBool();
}

QString IntensityDataItem::getXaxisTitle() const
{
    return getItem(P_XAXIS)->getItemValue(BasicAxisItem::P_TITLE).toString();
}

QString IntensityDataItem::getYaxisTitle() const
{
    return getItem(P_YAXIS)->getItemValue(BasicAxisItem::P_TITLE).toString();
}

bool IntensityDataItem::isZAxisLocked() const
{
    return getItem(P_ZAXIS)->getItemValue(AmplitudeAxisItem::P_LOCK_MIN_MAX).toBool();
}

void IntensityDataItem::setZAxisLocked(bool state)
{
    return getItem(P_ZAXIS)->setItemValue(AmplitudeAxisItem::P_LOCK_MIN_MAX, state);
}

QString IntensityDataItem::selectedAxesUnits() const
{
    ComboProperty combo = getItemValue(IntensityDataItem::P_AXES_UNITS).value<ComboProperty>();
    return combo.getValue();
}

QString IntensityDataItem::fileName(const QString& projectDir) const
{
    QString filename = getItemValue(IntensityDataItem::P_FILE_NAME).toString();
    return projectDir.isEmpty() ? filename : projectDir + QStringLiteral("/") + filename;
}

void IntensityDataItem::setLowerX(double xmin)
{
    getItem(P_XAXIS)->setItemValue(BasicAxisItem::P_MIN, xmin);
}

void IntensityDataItem::setUpperX(double xmax)
{
    getItem(P_XAXIS)->setItemValue(BasicAxisItem::P_MAX, xmax);
}

void IntensityDataItem::setLowerY(double ymin)
{
    getItem(P_YAXIS)->setItemValue(BasicAxisItem::P_MIN, ymin);
}

void IntensityDataItem::setUpperY(double ymax)
{
    getItem(P_YAXIS)->setItemValue(BasicAxisItem::P_MAX, ymax);
}

void IntensityDataItem::setLowerAndUpperZ(double zmin, double zmax)
{
    if (getLowerZ() != zmin)
        getItem(P_ZAXIS)->setItemValue(BasicAxisItem::P_MIN, zmin);

    if (getUpperZ() != zmax)
        getItem(P_ZAXIS)->setItemValue(BasicAxisItem::P_MAX, zmax);
}

void IntensityDataItem::setLowerZ(double zmin)
{
    getItem(P_ZAXIS)->setItemValue(BasicAxisItem::P_MIN, zmin);
}

void IntensityDataItem::setUpperZ(double zmax)
{
    getItem(P_ZAXIS)->setItemValue(BasicAxisItem::P_MAX, zmax);
}

void IntensityDataItem::setLogz(bool logz)
{
    getItem(P_ZAXIS)->setItemValue(AmplitudeAxisItem::P_IS_LOGSCALE, logz);
}

void IntensityDataItem::setInterpolated(bool interp)
{
    setItemValue(P_IS_INTERPOLATED, interp);
}

void IntensityDataItem::setXaxisTitle(QString xtitle)
{
    getItem(P_XAXIS)->setItemValue(BasicAxisItem::P_TITLE, xtitle);
}

void IntensityDataItem::setYaxisTitle(QString ytitle)
{
    getItem(P_YAXIS)->setItemValue(BasicAxisItem::P_TITLE, ytitle);
}

//! set zoom range of x,y axes to axes of input data
void IntensityDataItem::setAxesRangeToData()
{
    setLowerX(getXmin());
    setUpperX(getXmax());
    setLowerY(getYmin());
    setUpperY(getYmax());
}

//! Sets zoom range of X,Y axes, if it was not yet defined.

void IntensityDataItem::updateAxesZoomLevel()
{
    // set zoom range of x-axis to min, max values if it was not set already
    if (getUpperX() < getLowerX()) {
        setLowerX(getXmin());
        setUpperX(getXmax());
    }

    // set zoom range of y-axis to min, max values if it was not set already
    if (getUpperY() < getLowerY()) {
        setLowerY(getYmin());
        setUpperY(getYmax());
    }

    const int nx = static_cast<int>(m_data->getAxis(BornAgain::X_AXIS_INDEX).size());
    xAxisItem()->setItemValue(BasicAxisItem::P_NBINS, nx);
    const int ny = static_cast<int>(m_data->getAxis(BornAgain::Y_AXIS_INDEX).size());
    yAxisItem()->setItemValue(BasicAxisItem::P_NBINS, ny);
}

//! Init axes labels, if it was not done already.

void IntensityDataItem::updateAxesLabels()
{
    if (getXaxisTitle().isEmpty())
        setXaxisTitle(QString::fromStdString(m_data->getAxis(BornAgain::X_AXIS_INDEX).getName()));

    if (getYaxisTitle().isEmpty())
        setYaxisTitle(QString::fromStdString(m_data->getAxis(BornAgain::Y_AXIS_INDEX).getName()));
}

//! Sets min,max values for z-axis, if axes is not locked, and ranges are not yet set.

void IntensityDataItem::updateDataRange()
{
    if (isZAxisLocked())
        return;

    if (getLowerZ() <= getUpperZ())
        return;

    computeDataRange();
}

void IntensityDataItem::computeDataRange()
{
    QPair<double, double> minmax = dataRange();
    setLowerAndUpperZ(minmax.first, minmax.second);
}

//! Init zmin, zmax to match the intensity values range.
QPair<double, double> IntensityDataItem::dataRange() const
{
    const OutputData<double>* data = getOutputData();
    double min(*std::min_element(data->begin(), data->end()));
    double max(*std::max_element(data->begin(), data->end()));
    if (isLogz()) {
        if (max > 10000) {
            min = 1.0;
            max = max * 1.1;
        } else {
            min = max / 10000;
            max = max * 1.1;
        }
    } else {
        max = max * 1.1;
    }

    return QPair<double, double>(min, max);
}

const BasicAxisItem* IntensityDataItem::xAxisItem() const
{
    return dynamic_cast<const BasicAxisItem*>(getItem(P_XAXIS));
}

BasicAxisItem* IntensityDataItem::xAxisItem()
{
    return const_cast<BasicAxisItem*>(static_cast<const IntensityDataItem*>(this)->xAxisItem());
}

const BasicAxisItem* IntensityDataItem::yAxisItem() const
{
    return dynamic_cast<const BasicAxisItem*>(getItem(P_YAXIS));
}

BasicAxisItem* IntensityDataItem::yAxisItem()
{
    return const_cast<BasicAxisItem*>(static_cast<const IntensityDataItem*>(this)->yAxisItem());
}

const BasicAxisItem* IntensityDataItem::zAxisItem() const
{
    return dynamic_cast<const BasicAxisItem*>(getItem(P_ZAXIS));
}

BasicAxisItem* IntensityDataItem::zAxisItem()
{
    return const_cast<BasicAxisItem*>(static_cast<const IntensityDataItem*>(this)->zAxisItem());
}

//! Set axes viewport to original data.

void IntensityDataItem::resetView()
{
    setAxesRangeToData();
    if (!isZAxisLocked())
        computeDataRange();
}

MaskContainerItem* IntensityDataItem::maskContainerItem()
{
    return dynamic_cast<MaskContainerItem*>(getItem(IntensityDataItem::T_MASKS));
}

ProjectionContainerItem* IntensityDataItem::projectionContainerItem()
{
    return dynamic_cast<ProjectionContainerItem*>(getItem(IntensityDataItem::T_PROJECTIONS));
}

QDateTime IntensityDataItem::lastModified() const
{
    return m_last_modified;
}

void IntensityDataItem::setLastModified(const QDateTime &dtime)
{
    m_last_modified = dtime;
}
