// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/IntensityDataWidgets/ColorMapLabel.cpp
//! @brief     Implements class ColorMapLabel
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "ColorMapLabel.h"
#include "ColorMap.h"
#include "ColorMapCanvas.h"

ColorMapLabel::ColorMapLabel(ColorMap* colorMap, QWidget* parent) : StatusLabel(parent)
{
    if (colorMap)
        addColorMap(colorMap);
}

void ColorMapLabel::addColorMap(ColorMap* colorMap)
{
    if (m_colorMaps.contains(colorMap))
        return;

    m_colorMaps.push_back(colorMap);
    setColorMapLabelEnabled(colorMap, true);
}

void ColorMapLabel::addColorMap(ColorMapCanvas* colorMapCanvas)
{
    addColorMap(colorMapCanvas->colorMap());
}

//! Enables/disables label. If disabled, all colorMaps are disconnected and label is hiding.

void ColorMapLabel::setLabelEnabled(bool flag)
{
    foreach (ColorMap* colorMap, m_colorMaps)
        setColorMapLabelEnabled(colorMap, flag);

    setEnabled(flag);
}

//! Disconnects all color maps from the label.

void ColorMapLabel::reset()
{
    foreach (ColorMap* colorMap, m_colorMaps)
        setColorMapLabelEnabled(colorMap, false);

    m_colorMaps.clear();
}

void ColorMapLabel::onColorMapStatusString(const QString& text)
{
    setText(text);
}

//! Enables/disables showing of label for given color map.

void ColorMapLabel::setColorMapLabelEnabled(ColorMap* colorMap, bool flag)
{
    colorMap->setMouseTrackingEnabled(flag);
    setConnected(colorMap, flag);
}

//! Connects with colorMap's status string signal.

void ColorMapLabel::setConnected(ColorMap* colorMap, bool flag)
{
    if (flag) {
        connect(colorMap, SIGNAL(statusString(const QString&)), this,
                SLOT(onColorMapStatusString(const QString&)), Qt::UniqueConnection);
        connect(colorMap, &ColorMap::destroyed, this, &ColorMapLabel::onColorMapDestroyed);
    } else {
        disconnect(colorMap, SIGNAL(statusString(const QString&)), this,
                   SLOT(onColorMapStatusString(const QString&)));
    }
}

void ColorMapLabel::onColorMapDestroyed(QObject* obj)
{
    auto it = std::remove_if(m_colorMaps.begin(), m_colorMaps.end(),
                          [obj](ColorMap* cm){return cm == obj;});
    m_colorMaps.erase(it, m_colorMaps.end());
}
