// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/IntensityDataWidgets/ColorMapLabel.h
//! @brief     Defines class ColorMapLabel
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef COLORMAPLABEL_H
#define COLORMAPLABEL_H

#include "StatusLabel.h"
#include <QList>

class ColorMap;
class ColorMapCanvas;
class QResizeEvent;

//! The ColorMapLabel class shows status string as reported by ColorMap in a frame.
//! Can work with more than one ColorMap. Provides automatic adjustment of font size,
//! depending on available space in parent layout. Also doesn't trigger layout resize,
//! being happy with place it has.

class BA_CORE_API_ ColorMapLabel : public StatusLabel
{
    Q_OBJECT
public:
    ColorMapLabel(ColorMap* colorMap, QWidget* parent = nullptr);

    void addColorMap(ColorMap* colorMap);
    void addColorMap(ColorMapCanvas* colorMapCanvas);

    void setLabelEnabled(bool flag);

    void reset();

public slots:
    void onColorMapStatusString(const QString& text);

private slots:
    void onColorMapDestroyed(QObject* obj);

private:
    void setColorMapLabelEnabled(ColorMap* colorMap, bool flag);
    void setConnected(ColorMap* colorMap, bool flag);

    QList<ColorMap*> m_colorMaps;
};

#endif // COLORMAPLABEL_H
