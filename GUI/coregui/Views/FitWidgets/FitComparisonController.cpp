// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/FitWidgets/FitComparisonController.cpp
//! @brief     Implements class FitComparisonController
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "FitComparisonController.h"
#include "SessionModel.h"
#include "IntensityDataItem.h"
#include "PropertyRepeater.h"
#include "AxesItems.h"

FitComparisonController::FitComparisonController(QObject* parent)
    : QObject(parent)
    , m_appearanceRepeater(new PropertyRepeater(this))
    , m_xAxisRepeater(new PropertyRepeater(this))
    , m_yAxisRepeater(new PropertyRepeater(this))
    , m_zAxisRepeater(new PropertyRepeater(this))
    , m_relativeDiffItem(nullptr)
    , m_tempIntensityDataModel(new SessionModel("TempIntensityDataModel", this))
{
    createRelativeDifferenceItem();
}

IntensityDataItem* FitComparisonController::diffItem()
{
    return m_relativeDiffItem;
}

void FitComparisonController::setItems(IntensityDataItem* realDataItem,
                                       IntensityDataItem* simDataItem)
{
    double zmin = realDataItem->getLowerZ();
    double zmax = realDataItem->getUpperZ();
    simDataItem->setLowerAndUpperZ(zmin, zmax);

    m_appearanceRepeater->addItem(realDataItem);
    m_appearanceRepeater->addItem(simDataItem);
    m_appearanceRepeater->addItem(diffItem());

    m_xAxisRepeater->addItem(realDataItem->xAxisItem());
    m_xAxisRepeater->addItem(simDataItem->xAxisItem());
    m_xAxisRepeater->addItem(diffItem()->xAxisItem());

    m_yAxisRepeater->addItem(realDataItem->yAxisItem());
    m_yAxisRepeater->addItem(simDataItem->yAxisItem());
    m_yAxisRepeater->addItem(diffItem()->yAxisItem());

    m_zAxisRepeater->addItem(realDataItem->zAxisItem());
    m_zAxisRepeater->addItem(simDataItem->zAxisItem());
}

void FitComparisonController::clear()
{
    m_appearanceRepeater->clear();

    m_xAxisRepeater->clear();
    m_yAxisRepeater->clear();
    m_zAxisRepeater->clear();
}

void FitComparisonController::setActive(bool isActive)
{
    m_appearanceRepeater->setActive(isActive);
    m_xAxisRepeater->setActive(isActive);
    m_yAxisRepeater->setActive(isActive);
    m_zAxisRepeater->setActive(isActive);
}

void FitComparisonController::createRelativeDifferenceItem()
{
    m_tempIntensityDataModel->clear();

    m_relativeDiffItem = dynamic_cast<IntensityDataItem*>(
        m_tempIntensityDataModel->insertNewItem(Constants::IntensityDataType));
}
