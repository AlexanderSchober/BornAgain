// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Views/Components/OutputDataWidgets/centralplot.h
//! @brief     Defines class CentralPlot
//!
//! @homepage  http://bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef CENTRALPLOT_H
#define CENTRALPLOT_H

#include "qcustomplot.h"
#include "qcpdocumentobject.h"
#include <sstream>
#include "OutputDataItem.h"

class BA_CORE_API_ CentralPlot : public QCustomPlot
{
    Q_OBJECT

public:
    CentralPlot();
    virtual ~CentralPlot();

    void drawGraphOnMouseEvent(QPoint point);
    bool contains(QPoint point);
    QVector<QVector<double> > getHistogramData(QPoint point, bool isDrawLine = true);
    void drawPlot(OutputDataItem *outputDataItem, QCPColorGradient gradient);


    QCPColorMap *getColorMap() const;
    QCPRange getColorScaleRange() const;
    QCPColorMapData *getColorMapData() const;
    QString getStatusString() const;
    void setInterpolate(bool isInterpolate);
    void setZmin(double zmin);
    void setZmax(double zmax);
    void resetView();
    void setGradient(QCPColorGradient gradient);
    void setLogz(bool logz, bool isReplot  = true);
    bool isLogz();
    void showLinesOverMap(bool isLineVisible);
    void setXaxisTitle(QString xtitle);
    void setYaxisTitle(QString ytitle);

signals:
    void dataRangeChanged(QCPRange newRange);
    void xaxisRangeChanged(QCPRange newRange);
    void yaxisRangeChanged(QCPRange newRange);

private:
    void drawLineOverColorMap(double xPos, double yPos);
    QCPColorMap *m_colorMap;
    QCPColorScale *m_colorScale;
    QString statusString;
    QCPRange m_colorScaleRange;
    OutputDataItem *m_outputDataItem;
    QCPRange calculateDataRange();

};

#endif // CENTRALPLOT_H
